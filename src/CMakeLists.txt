# Executables (adjust paths if your .c files live in subfolders)
add_executable(hello_freertos hello_freertos.c)
add_executable(sleep        sleep.c)        # or sleep/sleep.c
add_executable(task_delay   task_delay.c)   # or task_delay/task_delay.c
add_executable(timer        timer.c)        # or timer/timer.c

set(APP_TARGETS hello_freertos sleep task_delay timer)

foreach(t ${APP_TARGETS})
  pico_set_program_name(${t} "${t}")
  pico_set_program_version(${t} "0.1")

  pico_enable_stdio_uart(${t} 0)
  pico_enable_stdio_usb(${t} 1)

  target_link_libraries(${t} PRIVATE
    pico_stdlib
    pico_multicore
    pico_async_context_freertos
    FreeRTOS-Kernel-Heap4
  )

  if(PICO_CYW43_SUPPORTED)
    target_link_libraries(${t} PRIVATE pico_cyw43_arch_none)
  endif()

  pico_add_extra_outputs(${t})
endforeach()

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

foreach(t ${APP_TARGETS})
  if(PICOTOOL)
    add_custom_target(flash_${t} ${PICOTOOL} load -f $<TARGET_FILE:${t}> DEPENDS ${t})
  endif()

  if(OPENOCD)
    add_custom_target(openocd_flash_${t}
      ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg
      -c "adapter speed 5000; program \"$<TARGET_FILE:${t}>\" verify reset exit"
      DEPENDS ${t})
  endif()
endforeach()
