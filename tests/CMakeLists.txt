enable_testing ()

function (KCDBUS_CREATE_TEST _generated_target_name _input_file_name)
    add_executable (${_generated_target_name}
        ${_input_file_name}
    )
    add_test (NAME ${_generated_target_name} COMMAND ${_generated_target_name} )
    target_link_libraries (${_generated_target_name} kdeconnect-qt Qt5::Test)
endfunction ()

kcdbus_create_test (tst_devicelist tst_devicelist.cpp)