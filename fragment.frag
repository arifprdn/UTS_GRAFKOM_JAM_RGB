#version 460 core
uniform float currentSecPointer;
uniform float currentMinPointer;
uniform float currentHourPointer;
uniform bool genapJam;
uniform bool genapMenit;
uniform bool genapDetik;
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;


layout (location = 0) out vec4 color; 
varying vec2 vPos;



void main()
{
    //background
    color = vec4(1.0, 1.0, 1.0, 1.0);

    //distance dari titik tengah untuk menggambar lingkaran
    float distance = length(vPos);
    

    //jam
    float dotHour = dot(normalize(vPos), vec2(cos(currentHourPointer), sin(currentHourPointer)));   
    
    //menggambar lingkaran terluar (lingkaran merah) untuk jam
    if (distance < 0.8 && distance > 0.7) {
        color = vec4(1.0, 1.0, 1.0, 1.0);
        dotHour = dotHour-sin(currentHourPointer);
        if (dotHour > 0) {
            color = color1;
        };
    };


    //menit
    float dotMinute = dot(normalize(vPos), vec2(cos(currentMinPointer), sin(currentMinPointer)));
    

    //kondisi yang terpengaruhi dari genap/ganjil dari jam untuk menentukan warna yg bergerak atau sebaliknya
    if (genapJam){
        if (distance < 0.6 && distance > 0.5) {
            color = vec4(1.0, 1.0, 1.0, 1.0);
            dotMinute = dotMinute-sin(currentMinPointer);
            if (dotMinute > 0) {
                color = color2;
            };
        };
    }else {
        if (distance < 0.6 && distance > 0.5) {
            color = color2;
            dotMinute = dotMinute-sin(currentMinPointer);
            if (dotMinute > 0) {
                color = vec4(1.0, 1.0, 1.0, 1.0);
            };
        };
    }



    float dotSecond = dot(normalize(vPos), vec2(cos(currentSecPointer), sin(currentSecPointer)));

    //detik

    if (genapMenit){
        if (distance < 0.4 && distance > 0.3) {
            color = vec4(1.0, 1.0, 1.0, 1.0);
            dotSecond = dotSecond-sin(currentSecPointer);
            if (dotSecond > 0) {
                color = color3;
            };
        };

    }else{
        if (distance < 0.4 && distance > 0.3) {
            color = color3;
            dotSecond = dotSecond-sin(currentSecPointer);
            if (dotSecond > 0) {
                color = vec4(1.0, 1.0, 1.0, 1.0);
            };
        };
    };


}