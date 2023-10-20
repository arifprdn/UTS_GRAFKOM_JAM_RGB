#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <string.h>
#include "Util.h"


//inisiasi warna
float color1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
float color2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
float color3[] = { 0.0f, 0.0f, 1.0f, 1.0f };

//inisiasi Variabel untuk diubah
float aturjam = 00.0f;
float aturmenit = 00.0f;
float aturdetik = 00.0f;

//variable radian  
float radianjam = 0.2617993878f;
float radianmenit = 0.0523598776f;
float radiandetik = 0.0523598776f;


//kecepatan tiap satuan waktu
float VelocitySecond = -0.10472/2;
float VelocityMinute = -0.0017453293/2;
float VelocityHour = -0.0001453859/2;


//inisiasi waktu
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

//variabel untuk menentukan jam menit detik 
float konversifloatmenitdetik = (aturdetik * 1.667f) / 100;
float menit = aturmenit + konversifloatmenitdetik;
float konversifloatjammenit = (aturmenit * 1.667f) / 100;
float jam = aturjam + konversifloatjammenit;
float detik = aturdetik;


//inisiasi pointer tiap satuan waktu(-4.7123889804 radian karena = -270 derajat agar start point berawal dari atas
float currentSecPointer = -4.7123889804f - (radiandetik * detik);
float currentMinPointer = -4.7123889804f - (radianmenit * menit);
float currentHourPointer = -4.7123889804f - (radianjam * jam);


//parsing dari float ke integer 
int jamInteger = (int)jam;
int menitInteger = (int)menit;
int detikInteger = (int)detik;


//inisiasi variable boolean untuk menentukan ganjil genap
bool genapJam = false;
bool genapMenit = false;
bool genapDetik = false;


//inisiasi variable untuk digunakan di Event handler
string Inputjam;
string InputDetik;
string tmpJam;
string Inputmenit;
int JamInput;
int MenitInput;
int DetikInput;

//fungsi keyCallback untuk Event Handler
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_I && action == GLFW_PRESS) {

        std::cout << "Setelah input selesai silahkan tekan tombol J untuk menerapkan jam!!" << std::endl;
        std::cout << "Masukkan Jam Berapa (format JAM:MENIT:DETIK | cth 20:30:00) : ";
        std::cin >> Inputjam;
        InputDetik.append(1, Inputjam[6]);
        InputDetik.append(1, Inputjam[7]);
        Inputmenit.append(1, Inputjam[3]);
        Inputmenit.append(1, Inputjam[4]);
        tmpJam.append(1, Inputjam[0]);
        tmpJam.append(1, Inputjam[1]);
        JamInput = std::stoi(tmpJam);
        MenitInput = std::stoi(Inputmenit);
        DetikInput = std::stoi(InputDetik);

        std::cout << JamInput << " " << MenitInput << " " << DetikInput << std::endl;


        jam = JamInput; // Update jam dengan jam dan menit yang dimasukkan
        menit = MenitInput;
        detik = DetikInput;

    };

    if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        // Hitung ulang posisi jarum jam dan menit
        currentHourPointer = -4.7123889804f - (radianjam * jam);
        currentMinPointer = -4.7123889804f - (radianmenit * menit);
        currentSecPointer = -4.7123889804f - (radiandetik * detik);
        
        if (MenitInput % 2 == 0) {
            genapMenit = true;
        }
        else {
            genapMenit = false;
        };

        if (JamInput % 2 == 0) {
            genapJam = true;
        }
        else {
            genapJam = false;  
        };

        
    };

    //Event Handler key E untuk mengganti warna secara acak
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        for (int i = 0;i < 3;i++) {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;
        }
        std::cout << color1[0] << " " << color1[1] << " " << color1[2] << " " << std::endl;
        std::cout << color2[0] << " " << color2[1] << " " << color2[2] << " " << std::endl;
        std::cout << color3[0] << " " << color3[1] << " " << color3[2] << " " << std::endl;
    }

    //Event Handler key S untuk menambah Velocity / kecepatan putaran
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        std::cout << " TAMBAH SPEED 2X LIPAT DARI YANG SEKARANG!! " << std::endl;
        VelocityHour = VelocityHour * 2;
        VelocityMinute = VelocityMinute * 2;
        VelocitySecond = VelocitySecond * 2;
        std::cout << VelocityHour << " " << VelocityMinute << " " << VelocitySecond << std::endl;
    }

    //Event Handler key R untuk mereset
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        std::cout << " RESET SPEED MENJADI NORMAL!! " << std::endl;
        currentHourPointer = -4.7123889804f;
        currentMinPointer = -4.7123889804f;
        currentSecPointer = -4.7123889804f;
        genapJam = true;
        genapMenit = true;
        genapDetik = true;
        VelocitySecond = 0;
        VelocityMinute = 0;
        VelocityHour = 0;

        VelocitySecond = -0.10472f / 2.0f;
        VelocityMinute = -0.0017453293f / 2.0f;
        VelocityHour = -0.0001453859f / 2.0f;
        std::cout << VelocityHour << " " << VelocityMinute << " " << VelocitySecond << std::endl;
    }


    //Event Handler key arrow up untuk menambah menit
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        std::cout << " Menit +1 !! " << std::endl;
        currentMinPointer = currentMinPointer - (0.1047197551f /2.0f);
        currentHourPointer = currentHourPointer - (0.0087266463f / 2.0f);
        currentSecPointer = -4.7123889804f;
        menitInteger = menitInteger + 1;
        if (menitInteger % 2 == 0) {
            genapMenit = true;
        }
        else {
            genapMenit = false;
        };
        /*
        std::cout << "Jam   : " << jam << std::endl;
        std::cout << "Menit : " << menit << std::endl;
        std::cout << "Detik : " << detik << std::endl;
        std::cout << "Jam INT   : " << jamInteger << std::endl;
        std::cout << "Menit INT : " << menitInteger << std::endl;
        std::cout << "Detik INT : " << detikInteger << std::endl;
        std::cout << "Genap Menit : " << genapMenit << std::endl;*/
    }

    //Event Handler key arrow down untuk mengurangi menit
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        std::cout << " Menit -1 !! " << std::endl;
        currentMinPointer = currentMinPointer + (0.1047197551f / 2.0f);
        currentHourPointer = currentHourPointer + (0.0087266463f / 2.0f);
        currentSecPointer = -4.7123889804f;
        menitInteger = menitInteger - 1;
        if (menitInteger % 2 == 0) {
            genapMenit = true;
        }
        else {
            genapMenit = false;
        };
        /*
        std::cout << "Jam   : " << jam << std::endl;
        std::cout << "Menit : " << menit << std::endl;
        std::cout << "Detik : " << detik << std::endl;
        std::cout << "Jam INT   : " << jamInteger << std::endl;
        std::cout << "Menit INT : " << menitInteger << std::endl;
        std::cout << "Detik INT : " << detikInteger << std::endl;
        std::cout << "Genap Menit: " << genapMenit << std::endl;*/
    }

    //Event Handler key arrow right untuk menambah jam
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        std::cout << " JAM +1 !! " << std::endl;
        currentHourPointer = currentHourPointer - (0.5235987756f / 2.0f);
        currentMinPointer = -4.7123889804f;
        currentSecPointer = -4.7123889804f;
        jamInteger = jamInteger + 1;
        if (jamInteger % 2 == 0) {
            genapJam = true;
            genapMenit = true;
        }
        else {
            genapJam = false;
            genapMenit = false;
        };
        std::cout << "Jam   : " << jam << std::endl;
        std::cout << "Menit : " << menit << std::endl;
        std::cout << "Detik : " << detik << std::endl;
        std::cout << "Jam INT   : " << jamInteger << std::endl;
        std::cout << "Menit INT : " << menitInteger << std::endl;
        std::cout << "Detik INT : " << detikInteger << std::endl;
        std::cout << "Genap Menit : " << genapMenit << std::endl;
    }

    //Event Handler key arrow left untuk mengurangi jam
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        std::cout << " JAM -1 !! " << std::endl;
        currentHourPointer = currentHourPointer + (0.5235987756f / 2.0f);
        currentMinPointer = -4.7123889804f;
        currentSecPointer = -4.7123889804f;
        jamInteger = jamInteger - 1;
        if (jamInteger % 2 == 0) {
            genapJam = true;
            genapMenit = true;
        }
        else {
            genapJam = false;
            genapMenit = false;
        };
        /*
        std::cout << "Jam   : " << jam << std::endl;
        std::cout << "Menit : " << menit << std::endl;
        std::cout << "Detik : " << detik << std::endl;
        std::cout << "Jam INT   : " << jamInteger << std::endl;
        std::cout << "Menit INT : " << menitInteger << std::endl;
        std::cout << "Detik INT : " << detikInteger << std::endl;
        std::cout << "Genap Menit : " << genapMenit << std::endl;*/
    }

   
}



int main(void)
{
   

    //menentukan boolean untuk mengetahui ganjil atau genap nya
    if (menitInteger % 2 == 0) {
        genapMenit = true;
    }
    else {
        genapMenit = false;
    }

    if (jamInteger % 2 == 0) {
        genapJam = true;
    }
    else {
        genapJam = false;
    }

    if (detikInteger % 2 == 0) {
        genapDetik = true;
    }
    else {
        genapDetik = false;
    }
    

    /*
    std::cout << "Jam   : " << jam << std::endl;
    std::cout << "Menit : " << menit << std::endl;
    std::cout << "Detik : " << detik << std::endl;
    std::cout << "Jam INT   : " << jamInteger << std::endl;
    std::cout << "Menit INT : " << menitInteger << std::endl;
    std::cout << "Detik INT : " << detikInteger << std::endl;
    std::cout << "GenapMenit : " << genapMenit << std::endl;*/



    std::cout << " TOMBOL i : menginput waktu yang ingin dirubah" << std::endl;
    std::cout << " TOMBOL j : untuk menerapkan waktu setelah diinput" << std::endl;
    std::cout << " TOMBOL e : merubah warna secara random" << std::endl;
    std::cout << " TOMBOL s : menambah kecepatan" << std::endl;
    std::cout << " TOMBOL r : mereset jam seperti awal" << std::endl;
    std::cout << " TOMBOL ARROW UP : menambah menit sebanyak 1 ketika ditekan" << std::endl;
    std::cout << " TOMBOL ARROW DOWN : mengurangi menit sebanyak 1 ketika ditekan" << std::endl;
    std::cout << " TOMBOL ARROW RIGHT : menambah jam sebanyak 1 ketika ditekan" << std::endl;
    std::cout << " TOMBOL ARROW LEFT : mengurangi jam sebanyak 1 ketika ditekan" << std::endl;


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode windowand its OpenGL context */
    window = glfwCreateWindow(640, 640, "UTS JAM", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glewInit();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    float vertices[] = {
        1.0, 1.0,
        -1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0 };

    unsigned int indexArr[] = {
        0, 1, 2, 0, 2, 3
    };


    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    //std::cout << vertexBuffer << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    //std::cout << indexBuffer << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indexArr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


    // membaca file vertex dan fragment dan disimpan di string
    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);


    // GL_BLEND agar transparansi bisa diatur 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


    glewExperimental = GL_TRUE;
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    //inisiasi variabel Location agar dapat menyimpan lokasi dari main program
    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinPointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");
    GLint color1Loc = glGetUniformLocation(program, "color1");
    GLint color2Loc = glGetUniformLocation(program, "color2");
    GLint color3Loc = glGetUniformLocation(program, "color3");
    GLboolean genapJamLoc = glGetUniformLocation(program, "genapJam");
    GLboolean genapMenitLoc = glGetUniformLocation(program, "genapMenit");
    GLboolean genapDetikLoc = glGetUniformLocation(program, "genapDetik");


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //currentTime didapat dari glfwGetTime yg berfungsi sebagai penghitung lamanya waktu setelah dirender pertama kali
        currentTime = glfwGetTime();
 
        //float TestcurrentTime = glfwGetTime();
        //std::cout << "Current Time: " << TestcurrentTime << " seconds" << std::endl;

        //menghitung perbedaan waktu setiap loop berjalan
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;


        //pointer untuk menggerakkan lingkaran setiap loop berjalan
        currentSecPointer = currentSecPointer + (deltaTime * VelocitySecond);
        currentMinPointer = currentMinPointer + (deltaTime * VelocityMinute);
        currentHourPointer = currentHourPointer + (deltaTime * VelocityHour);


        //glUniform untuk mentransfer data ke shader
        glUniform1f(currentSecondPointerLoc, currentSecPointer );
        glUniform1f(currentMinutePointerLoc, currentMinPointer );
        glUniform1f(currentHourPointerLoc, currentHourPointer );
        glUniform1f(genapJamLoc, genapJam);
        glUniform1f(genapMenitLoc, genapMenit);
        glUniform1f(genapDetikLoc, genapDetik);
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], 1.0f);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], 1.0f);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], 1.0f);



        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap frontand back buffers */
        glfwSwapBuffers(window);

        /* Poll forand process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}