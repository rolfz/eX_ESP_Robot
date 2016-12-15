#ifndef EX_ESP_CONFIG_H
#define EX_ESP_CONFIG_H

#define  USE_UART

#ifndef USE_UART
 #define USE_2_SERVOS
#endif

/// Параметры шины I2C и UART ///
#define  I2C_SPEED                  400000
#define  SERIAL_SPEED               57600
//#define  K_bat                      0.004581469370719
#define  K_bat                      1.5*0.004581469370719 //rz: alternative battery level divider

///    Параметры модуля MPU6050      ///
//============= start ================//
#define  ACCEL_SCALE_G              8192             // (2G range) G = 8192
#define  ACCEL_WEIGHT               0.01
#define  GYRO_BIAS_WEIGHT           0.005
// MPU6000 sensibility   (0.0609 => 1/16.4LSB/deg/s at 2000deg/s, 0.03048 1/32.8LSB/deg/s at 1000deg/s)
#define  Gyro_Gain                  0.03048
#define  Gyro_Scaled(x)             x*Gyro_Gain      //Return the scaled gyro raw data in degrees per second
#define  RAD2GRAD                   57.2957795
#define  GRAD2RAD                   0.01745329251994329576923690768489
//============== end =================//

// Задаём параметры ШД и тип драйвера //
//============= start ================//
#define  MICROSTEPPING              16    // 8, 16, 32
#define  ANGLE_PER_STEP             1.8   // 0.9, 1.8
#define  K_MOTOR_SPEED              MICROSTEPPING * 360 / ANGLE_PER_STEP 
#define  PRE_DIR_STROBE             27    // 25 - 640 ns, 27 - 690ns, 28 - 740 ns
//============== end =================//

///       Конструктивная секция      ///
//============= start ================//
// в аторской версии используются колёса диаметром D = 100 мм
// следовательно за один оборот колеса робот проезжает расстояние Pi*D = 314.15652 мм
// один оборот мотора - это 200 шагов по 1.8 градуса или 1600 микрошагов при 1/8
// управляющее значение максимальной скорости - 500
// это значение умноженное на 23 давало моторную скорость 
// и определяло период следование управляющих импульсов 173.913 интервала по 0.5 мкс
// или период в 86.9565 мкс
// что соответствавало частоте 11.5 кГц (она же 500*23=11500)
// при этих частотах мотор совершал 7.1875 полных оборота в секунду
// что соответствовало линейной скорости  2258 мм/сек (135.48 м/мин)(8.1288 км/ч)

// For the original robot, a wheel with D = 100 mm was used
// For this wheel, the distance for one turn (Périmeter) will be:  Pi*D = 314.15652 mm
// The number of steps for the used motor is  200 steps and 1.8 degrés equivalent to 1600 microsteps at 1/8 
// for a setup with microsteps at 1/16, the number of microsteps will double and become 3200 steps.

// The controlling value for maximum speed is 500 
// This number multiplied by 23 gives the motor speed
// This allows us to calculate the period of one cycle equivalent to 173.913 us. As the puls is 1/2 of the period
// this results in a pulse of 86.9565 us.
// rz rem: my calculation of 1/period = 1/11500 = 86.9565us and a plus if 43us...... to be checked !!!!!!!!!!!!!!!!
// which corresponds to a frequency of 11.5 kHz (500*23=11500) 
// with this frequency, the motor makes 7.1875 turns per second 
// which corrresponds to a linear speed of 2258 mm/s = 8.1288 km/h
 
#define  MAX_SPEED_LINEAR           8.5   // км/ч
//#define  VHEEL_DIAMETR              108   // мм
#define VHEEL_DIAMETR               94 //rz: mm

#define  MAX_TURN                   MAX_SPEED_LINEAR * 1000000 / 3600 / VHEEL_DIAMETR / PI  // обороты в секунду // max tours/secondes
#define  MAX_FREQUENCY              MAX_TURN * 360 / ANGLE_PER_STEP * MICROSTEPPING         // максимальная частота следования импульсов STEP (Гц)
                                                                                            // Maximum motor pulse frequency (STEP)

//============== end =================//


///     Параметры управляемости      ///
//============= start ================//
#define  ZERO_SPEED                 25000
#define  MAX_ACCEL                  8
#define  MAX_CONTROL_OUTPUT         500

// NORMAL MODE = smooth, moderately
#define  MAX_THROTTLE               480      // дроссель, скорость // accellerator speed
#define  MAX_STEERING               130      // руление, поворачиваемость // max steering
#define  MAX_TARGET_ANGLE           12       // угол наклона // max tilt angle

// PRO MODE = more aggressive
#define  MAX_THROTTLE_PRO           680
#define  MAX_STEERING_PRO           250 
#define  MAX_TARGET_ANGLE_PRO       20
//============== end =================//

///         PID-параметры            ///
//============= start ================//
// Условия управления по умолчанию 
#define  KP                         0.19    // альтернативные значения: 0.20, 0.22        
#define  KD                         30      // 26 28        
#define  KP_THROTTLE                0.07    // 0.065, 0.08
#define  KI_THROTTLE                0.04    // 0.05
// Прирост управления при поднятии робота из лежачего положения
#define  KP_RAISEUP                 0.16
#define  KD_RAISEUP                 40
#define  KP_THROTTLE_RAISEUP        0       // При поднятии скорость моторов не контролируется
#define  KI_THROTTLE_RAISEUP        0.0
#define  ITERM_MAX_ERROR            40      // Iterm windup constants
#define  ITERM_MAX                  5000
//============== end =================//

/// Параметры серво-привода ///
//============= start ================//
// максимальное значение периода 20 миллисекунд и при длительности такта 10 мкc  = 2000 тактов
// положительный строб импульса управления изменяется в пределах:
// минимальное  - 0.6 мс, среднее - 1.5 мс и наибольшее - 2.4 мс или в периодах 60-150-240
//  
#define  SERVO_AUX_NEUTRO           150     // нейтральное положение серво-привода
#define  SERVO_MIN_PULSEWIDTH       80
#define  SERVO_MAX_PULSEWIDTH       220
//============== end =================//
#endif // EX_ESP_CONFIG_H
