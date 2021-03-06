

#include "zealot_predefine.h"



int test_zce_snprintf()
{
    char out_buffer[1024 + 1];
    size_t cur_len = 0;
    size_t buf_max_len = 1024;

    int int_data = 123456;
    bool bool_data = false;
    ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? Haha!\n", int_data, bool_data);
    printf("%s",out_buffer);

    ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data= Haha!\n", int_data, bool_data);
    printf("%s", out_buffer);

    ZCE_LIB::zce_snprintf(out_buffer, 10, cur_len, "int_data=%? bool_data= %? Haha!\n", int_data, bool_data);
    std::cout << (out_buffer) << std::endl;

    ZCE_LIB::zce_snprintf(out_buffer, 15, cur_len, "int_data=%? bool_data= %? Haha!\n", int_data, bool_data);
    std::cout << (out_buffer) << std::endl;

    ZCE_LIB::zce_snprintf(out_buffer, 20, cur_len, "int_data=%? bool_data= %? Haha!\n", int_data, bool_data);
    std::cout << (out_buffer) << std::endl;

    ZCE_LIB::zce_snprintf(out_buffer, 30, cur_len, "int_data=%? bool_data= %? Haha!\n", int_data, bool_data);
    std::cout << (out_buffer) << std::endl;

    double double_data = 123456789012.1234f;
    ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data= %? double_data = %?Haha!\n",
                          int_data,
                          bool_data,
                          double_data);
    std::cout << (out_buffer) << std::endl;
    return 0;
}

int test_printf_int()
{
    printf("+-----------------------------------------------------------+\n");
    int int_data = 123456;
    printf("[%d]\n", -1 * int_data);
    printf("[%+d]\n", int_data);
    printf("[%25.8u]\n", int_data);
    printf("[%+25.8d]\n", int_data);
    printf("[%25.8u]\n", int_data);
    printf("[%25.0d]\n", int_data);
    printf("[%#25.0x]\n", int_data);
    printf("[%#025x]\n", int_data);
    printf("[%25.8x]\n", int_data);
    printf("[%.8d]\n", int_data);
    printf("[%.0d]\n", int_data);
    printf("+-----------------------------------------------------------+\n");
    char out_buffer[1024 + 1];
    size_t cur_len = 0;
    size_t buf_max_len = 1024;
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, -1 * int_data, ZCE_LIB::BASE_DECIMAL, 0, size_t(-1));
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 0, size_t(-1), ZCE_LIB::FMT_PLUS);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 25, 8, ZCE_LIB::FMT_UNSIGNED);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 25, 8, ZCE_LIB::FMT_PLUS);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 25, 8, ZCE_LIB::FMT_PLUS | ZCE_LIB::FMT_UNSIGNED);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 25, 0, ZCE_LIB::FMT_PLUS | ZCE_LIB::FMT_UNSIGNED);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_HEXADECIMAL, 25, 0, ZCE_LIB::FMT_NUM);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_HEXADECIMAL, 25, 0, ZCE_LIB::FMT_NUM | ZCE_LIB::FMT_ZERO);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_HEXADECIMAL, 25, 8, ZCE_LIB::FMT_ZERO);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 0, 8, 0);
    printf("[%.*s]\n", (int)cur_len, out_buffer);
    ZCE_LIB::fmt_int64(out_buffer, buf_max_len, cur_len, int_data, ZCE_LIB::BASE_DECIMAL, 0, 0, 0);
    printf("[%.*s]\n", (int)cur_len, out_buffer);

    printf("+-----------------------------------------------------------+\n");
    return 0;
}

int test_fmt_strncpy(int /*argc*/, char * /*argv*/[])
{
    const size_t BUFFER_LEN = 1024;
    size_t use_len = 0;
    char buffer [BUFFER_LEN + 1];
    ZCE_LIB::zce_strnsplice(buffer, BUFFER_LEN, use_len, "ABC", "efghi");
    std::cout << buffer << std::endl;
    return 0;
}

int printf_double()
{
    char out_buffer[1024 + 1];
    size_t cur_len = 0;
    size_t buf_max_len = 1024;
    //double test_double = 123456789012.123456789;
    double test_double = 123456789012.8;
    //fmtfp(out_buffer,&cur_len,buf_max_len,test_double,0,0,0);
    out_buffer[cur_len] = '\0';
    printf("%s\n", out_buffer);

    int dec, sign;
    test_double = 1.000000000;
    ZCE_LIB::fcvt_r(test_double,
                   5,
                   &dec,
                   &sign,
                   out_buffer,
                   1024
                  );
    test_double = 0.000000000;
    ZCE_LIB::ecvt_r(
        test_double,
        5,
        &dec,
        &sign,
        out_buffer,
        1024
    );


#ifdef ZCE_OS_WINDOWS
    _gcvt_s(out_buffer,
            1024,
            test_double,
            5
           );
#endif

    test_double = 0.000000012345678912;
    ZCE_LIB::fcvt_r(
        test_double,
        10,
        &dec,
        &sign,
        out_buffer,
        1024
    );

    ZCE_LIB::ecvt_r(
        test_double,
        5,
        &dec,
        &sign,
        out_buffer,
        1024
    );

#ifdef ZCE_OS_WINDOWS
    _gcvt_s(out_buffer,
            1024,
            test_double,
            5
           );
#endif


    cur_len = 0;
    test_double = -1.12345678e+100;
    ZCE_LIB::fmt_double(out_buffer,
                        buf_max_len,
                        cur_len,
                        test_double,
                        10,
                        5,
                        0);

    ZCE_LIB::fmt_double(out_buffer,
                        buf_max_len,
                        cur_len,
                        test_double,
                        20,
                        5,
                        ZCE_LIB::FMT_EXPONENT | ZCE_LIB::FMT_MINUS);

    test_double = 1.0000000;
    ZCE_LIB::fmt_double(out_buffer,
                        buf_max_len,
                        cur_len,
                        test_double,
                        10,
                        5,
                        0);

    printf ("%s\n", out_buffer);
    printf ("%10.5f\n", test_double);
    ZCE_LIB::fmt_double(out_buffer,
                        buf_max_len,
                        cur_len,
                        test_double,
                        20,
                        5,
                        ZCE_LIB::FMT_EXPONENT | ZCE_LIB::FMT_LEFT_ALIGN | ZCE_LIB::FMT_UP | ZCE_LIB::FMT_PLUS);
    printf ("%s\n", out_buffer);
    printf ("%-+20.5E\n", test_double);

    printf ("-------------------------------------------------------------\n");

    test_double = -0.0000000123456;
    ZCE_LIB::fmt_double(out_buffer,
                        buf_max_len,
                        cur_len,
                        test_double,
                        20,
                        9,
                        0);
    printf ("%s\n", out_buffer);
    printf ("%20.9f\n", test_double);
    ZCE_LIB::fmt_double(out_buffer,
                        buf_max_len,
                        cur_len,
                        test_double,
                        20,
                        5,
                        ZCE_LIB::FMT_EXPONENT | ZCE_LIB::FMT_LEFT_ALIGN | ZCE_LIB::FMT_UP | ZCE_LIB::FMT_PLUS);
    printf ("%s\n", out_buffer);
    printf ("%-+20.5E\n", test_double);

    printf ("-------------------------------------------------------------\n");
    printf ("-------------------------------------------------------------\n");

    return 0;
}


int test_cpp_log_out(int /*argc*/, char * /*argv*/[])
{

    ZCE_LogTrace_Plus::instance()->write_logmsg(RS_DEBUG, "my love=%? ", "ABCDEFG");

    ZCE_LogTrace_Plus::instance()->write_logmsg(RS_DEBUG, "my love=%? you love=%?", "ABCDEFG", 1234567890);

    ZCE_LogTrace_Plus::instance()->write_logmsg(RS_DEBUG, "one love=%? two love= %? three love=%?",
                                                "ABCDEFG",
                                                1.1,
                                                12345);

    return 0;
}




char out_buffer[1024 + 1];
size_t cur_len = 0;
size_t buf_max_len = 1024;


const size_t A_TEST_TIMES = 1024 * 1000;
const size_t B_TEST_TIMES = 1024 * 1000;

const size_t STR_TIME_LEN = 256;
char str_time[STR_TIME_LEN];

int int_data = 123456;
bool bool_data = false;
double double_data = 123456789012.1234f;
const char cstr_data[] = "I love you.";
std::string stdstr_data = "You love me.";


int test_out_buffer(int /*argc*/,char * /*argv*/[])
{
    const std::string def("You love me.");
    ZCE_LIB::String_Out_Helper abc(def);

    ZCE_Progress_Timer progress_timer;
    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
                              int_data,
                              bool_data,
                              double_data,
                              cstr_data,
                              stdstr_data
                             );

    }
    progress_timer.end();
    std::cout << "out string:[" << out_buffer << "]" << std::endl;
    std::cout << "zce_snprintf use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        ZCE_LIB::foo_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
            int_data,
            bool_data,
            double_data,
            cstr_data,
            stdstr_data
            );

    }
    progress_timer.end();
    std::cout << "out string:[" << out_buffer << "]" << std::endl;
    std::cout << "foo_snprintf use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        snprintf(out_buffer, buf_max_len, "int_data=%d bool_data=%s double_data=%e cstr_data=%s stdstr_data=%s Haha!\n",
                 int_data,
                 bool_data ? "TRUE" : "FALSE",
                 double_data,
                 cstr_data,
                 stdstr_data.c_str());

    }
    progress_timer.end();
    std::cout << "out string:[" << out_buffer << "]" << std::endl;
    std::cout << "snprintf use " << progress_timer.elapsed_sec() << " sec ." << std::endl;


    progress_timer.restart();
    std::ostringstream ostr_stream;
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        ostr_stream.str("");
        ostr_stream << "int_data="
                    << int_data
                    << " bool_data="
                    << (bool_data ? "TRUE" : "FALSE")
                    << " double_data="
                    << double_data
                    << " cstr_data="
                    << cstr_data
                    << " stdstr_data="
                    << stdstr_data
                    << " Haha!\n";
    }
    progress_timer.end();
    std::cout << "out string:[" << ostr_stream.str() << "]" << std::endl;
    std::cout << "ostringstream use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
                              ZCE_LIB::Int_Out_Helper(int_data, ZCE_LIB::BASE_HEXADECIMAL, 32, 0, ZCE_LIB::FMT_ZERO),
                              bool_data,
                              ZCE_LIB::Double_Out_Helper(double_data, 16, 3),
                              ZCE_LIB::String_Out_Helper(cstr_data, 30),
                              ZCE_LIB::String_Out_Helper(stdstr_data.c_str(), stdstr_data.length())
                             );

    }
    progress_timer.end();
    std::cout << "out string:[" << out_buffer << "]" << std::endl;
    std::cout << "zce_snprintf format use " << progress_timer.elapsed_sec() << " sec ." << std::endl;


    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        ZCE_LIB::foo_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
            ZCE_LIB::Int_Out_Helper(int_data, ZCE_LIB::BASE_HEXADECIMAL, 32, 0, ZCE_LIB::FMT_ZERO),
            bool_data,
            ZCE_LIB::Double_Out_Helper(double_data, 16, 3),
            ZCE_LIB::String_Out_Helper(cstr_data, 30),
            ZCE_LIB::String_Out_Helper(stdstr_data.c_str(), stdstr_data.length())
            );

    }
    progress_timer.end();
    std::cout << "out string:[" << out_buffer << "]" << std::endl;
    std::cout << "foo_snprintf format use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        snprintf(out_buffer, buf_max_len, "int_data=%032x bool_data=%s double_data=%16.3f cstr_data=%30s stdstr_data=%28s Haha!\n",
                 int_data,
                 bool_data ? "TRUE" : "FALSE",
                 double_data,
                 cstr_data,
                 stdstr_data.c_str());

    }
    progress_timer.end();
    std::cout << "out string:[" << out_buffer << "]" << std::endl;
    std::cout << "snprintf format use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    for (size_t i = 0; i < A_TEST_TIMES; ++i)
    {
        ostr_stream.str("");
        ostr_stream << "int_data="
                    << std::setw(32) << std::hex << std::setfill('0')
                    << int_data
                    << " bool_data="
                    << (bool_data ? "TRUE" : "FALSE")
                    << " double_data= "
                    << std::fixed << std::setw(16) << std::setprecision(3) << std::setfill(' ')
                    << double_data
                    << " cstr_data="
                    << std::setw(30)
                    << cstr_data
                    << " stdstr_data="
                    << std::setw(28)
                    << stdstr_data
                    << " Haha!\n";
    }
    progress_timer.end();
    std::cout << "out string:[" << ostr_stream.str() << "]" << std::endl;
    std::cout << "ostringstream format use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    return 0;

}

int test_out_file()
{
    ZCE_Progress_Timer progress_timer;
    progress_timer.restart();
    std::ofstream of_stream_1("FILE_A1.txt", std::ios::trunc | std::ios::ate);
    for (size_t i = 0; i < B_TEST_TIMES; ++i)
    {
        ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
                              int_data,
                              bool_data,
                              double_data,
                              cstr_data,
                              stdstr_data
                             );
        of_stream_1.write(out_buffer, cur_len);
    }
    of_stream_1.close();

    progress_timer.end();

    std::cout << "zce_snprintf with ofstream use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    FILE *file_p = fopen("FILE_A2.txt", "wb");
    for (size_t i = 0; i < B_TEST_TIMES; ++i)
    {
        fprintf(file_p, "int_data=%d bool_data=%s double_data=%e cstr_data=%s stdstr_data=%s Haha!\n",
                int_data,
                bool_data ? "TRUE" : "FALSE",
                double_data,
                cstr_data,
                stdstr_data.c_str());
    }
    fclose(file_p);
    progress_timer.end();
    std::cout << "fprintf use " << progress_timer.elapsed_sec() << " sec ." << std::endl;


    progress_timer.restart();
    std::ofstream of_stream("FILE_A3.txt", std::ios::trunc | std::ios::ate);
    for (size_t i = 0; i < B_TEST_TIMES; ++i)
    {
        of_stream << "int_data="
                  << int_data
                  << " bool_data="
                  << (bool_data ? "TRUE" : "FALSE")
                  << " double_data= "
                  << double_data
                  << " cstr_data="
                  << cstr_data
                  << " stdstr_data="
                  << stdstr_data
                  << " Haha!\n";
    }
    of_stream.close();
    progress_timer.end();

    std::cout << "ofstream use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    return 0;
}


int test_out_file_stream()
{
    ZCE_Progress_Timer progress_timer;
    progress_timer.restart();
    std::ofstream of_stream_1("FILE_B1.txt", std::ios::trunc | std::ios::ate);
    for (size_t i = 0; i < B_TEST_TIMES; ++i)
    {
        ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
                              int_data,
                              bool_data,
                              double_data,
                              cstr_data,
                              stdstr_data
                             );
        of_stream_1.write(out_buffer, cur_len);
    }
    of_stream_1.close();

    progress_timer.end();

    std::cout << "zce_snprintf with ofstream use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    progress_timer.restart();
    ZCE_HANDLE file_handle = ZCE_LIB::open("FILE_B2.txt", O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IWRITE | S_IREAD);
    for (size_t i = 0; i < B_TEST_TIMES; ++i)
    {
        ZCE_LIB::zce_snprintf(out_buffer, buf_max_len, cur_len, "int_data=%? bool_data=%? double_data=%? cstr_data=%? stdstr_data=%? Haha!\n",
                              int_data,
                              bool_data,
                              double_data,
                              cstr_data,
                              stdstr_data
                             );
        ZCE_LIB::write(file_handle, out_buffer, cur_len);
    }
    ZCE_LIB::close(file_handle);
    progress_timer.end();
    std::cout << "zce_snprintf  with  ZCE_LIB::write use" << progress_timer.elapsed_sec() << " sec ." << std::endl;


    progress_timer.restart();
    std::ofstream of_stream_3("FILE_B3.txt", std::ios::trunc | std::ios::ate);
    for (size_t i = 0; i < B_TEST_TIMES; ++i)
    {
        of_stream_3 << "int_data="
                    << int_data
                    << " bool_data="
                    << (bool_data ? "TRUE" : "FALSE")
                    << " double_data= "
                    << double_data
                    << " cstr_data="
                    << cstr_data
                    << " stdstr_data="
                    << stdstr_data
                    << " Haha!\n";
    }
    of_stream_3.close();
    progress_timer.end();

    std::cout << "ofstream use " << progress_timer.elapsed_sec() << " sec ." << std::endl;

    return 0;
}


int test_log_debug(int , char * [])
{
    ZCE_BACKTRACE_STACK(RS_DEBUG);
    char dbg_ptr[916];
    memset(dbg_ptr,0x68,916);
    ZCE_TRACE_POINTER_DATA(RS_DEBUG,(const unsigned char *)dbg_ptr,916);
    return 0;
}

