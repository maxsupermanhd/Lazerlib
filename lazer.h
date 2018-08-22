/*! \mainpage Draw with lazer!
 * 
 * \section install_sec Installation
 * 	Устанавливается в папку библиотек arduino и подключается строкой #include “Lazer.h”
 *
 * \section startwork Начало работы
 * \subsection step2 Step 2: Подключение
 * 	Чтобы определить пары выводов шагового двигателя (A+,A-,B+,B-) не подключая его к драйверу необходимо методом перебора зымыкать между собой пары выводов и вращать вал двигателя, например у вас следующие цвета выводов Черный(Чр), Синий(Сн), Красный(Кр), Желтый(Жл), замыкаете между собой Чр+Сн и Кр+Жл, если вал начал вращаться с усилием и шажками, то поздравляю вы нашли пары, если же нет продолжайте перебор Чр+Кр и Сн+Жл, и так далее. Найдя пары подключайте к драйверу и проверяйте направление вращения, угадали хорошо, если нет то меняйте местами провода в паре, например у вас пары Чр+Сн и Кр+Жл, то меняете местами одну пару Сн+Чр, вторую не трогаете Кр+Жл и опять проверяете паправление вращения, угадали хорошо, если нет то продолжаете перебор: Чр+Сн и Жл+Кр, Сн+Чр и Жл+Кр.
 * 	После правильного или не очень подключения шаговиков существует два варианта начала работы с библиотекой.  Оба рабочие и могут быть применимы в реальных проектах
 * \subsection step21 Step 2.1: InitLazer(…)
 * 	Этот способ использует функцию InitLazer. Достаточно вызвать её с нужными аргументами и всё будет задано и откалибровано за вас. Аргументы смотреть в справочнике функций.
 * \subsection step22 Step 2.2: Руками
 * 	Этот способ больше подходит тем, кто хочет работать с библиотекой на уровне ниже. Достаточно указать значение переменных, которые отвечают за пины и назначить им режим работы OUTPUT. Так же крайне советуем вызват сразу после этого функцию calebrateLaser для выравнивания координатной сетки. Все глобальные переменные и их описания можно будет найти в справочнике.
 * \section start Hello GitHub!
	Для проверки работы шаговиков, сразу после калибровки в loop() можно вызвать DrawGitHubLogo с параметром speed. Если перед собой вы увидите нечто похожее на логотип GitHub то это означает что все настроено правильно.
 *
 */

/*! \file Lazer.h
    \brief Сама библиотека.
    Её надо подключить.
*/
/// Отвечает за первый пин первого шагового двигателя
byte _LAZER_STEP_PIN_1 = 0;

/// Отвечает за второй пин первого шагового двигателя
byte _LAZER_DIRECTION_PIN_1 = 0;

/// Отвечает за третий пин первого шагового двигателя
byte _LAZER_ENABLE_PIN_1 = 0;

/// Отвечает за первый пин второго шагового двигателя
byte _LAZER_STEP_PIN_2 = 0;

/// Отвечает за второй пин второго шагового двигателя
byte _LAZER_DIRECTION_PIN_2 = 0;

/// Отвечает за третий пин второго шагового двигателя
byte _LAZER_ENABLE_PIN_2 = 0;

/// Пин, который отвечает за включение лазера
byte _LAZER_CONTROLL_PIN_1 = 0;

int _LAZER_NOW_LAZER_IN_X = 0;

int _LAZER_NOW_LAZER_IN_Y = 0;

/*! \defgroup BasicDraw Базовые движения для рисования
    \brief С помощью этих функций можно нарисовать абсолютно все!
    @{
*/

/*!
Включает или выключает лазер.
\param Color комманда 0-выключить, 1-включить
*/
void SetLazer(int Color)
{
  switch(Color)
  {
    case 0:
      pinMode(_LAZER_CONTROLL_PIN_1, OUTPUT);
    break;
    case 1:
      pinMode(_LAZER_CONTROLL_PIN_1, INPUT);
    break;
  }
}

/*!
Двигает лазер в нужную координату с определенной скоростью.
\param TargetX Координата по оси X
\param TargetY Координата по оси Y
\param Drspeed Скорость. Значения меньше 1 на свой страх и риск!
*/
void SetLazerPos(int TargetX, int TargetY, float Drspeed)
{
  if(TargetX > _LAZER_NOW_LAZER_IN_X)
  {
    digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
    digitalWrite(_LAZER_DIRECTION_PIN_2, HIGH);
    for (int i = _LAZER_NOW_LAZER_IN_X; i != TargetX; i++)
    {
      digitalWrite(_LAZER_STEP_PIN_2, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_2, LOW);
      delay(Drspeed);
    }
    analogWrite(_LAZER_ENABLE_PIN_2, 100);
    _LAZER_NOW_LAZER_IN_X+=TargetX-_LAZER_NOW_LAZER_IN_X;
  }
  else
  {
    digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
    digitalWrite(_LAZER_DIRECTION_PIN_2, LOW);
    for (int i = _LAZER_NOW_LAZER_IN_X; i != TargetX; i--)
    {
      digitalWrite(_LAZER_STEP_PIN_2, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_2, LOW);
      delay(Drspeed);
    }
    analogWrite(_LAZER_ENABLE_PIN_2, 100);
    _LAZER_NOW_LAZER_IN_X-=_LAZER_NOW_LAZER_IN_X-TargetX;
  }

  if(TargetY > _LAZER_NOW_LAZER_IN_Y)
  {
    digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
    digitalWrite(_LAZER_DIRECTION_PIN_1, HIGH);
    for (int i = _LAZER_NOW_LAZER_IN_Y; i != TargetY; i++)
    {
      digitalWrite(_LAZER_STEP_PIN_1, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_1, LOW);
      delay(Drspeed);
    }
    analogWrite(_LAZER_ENABLE_PIN_1, 100);
    _LAZER_NOW_LAZER_IN_Y+=TargetY-_LAZER_NOW_LAZER_IN_Y;
  }
  else
  {
    digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
    digitalWrite(_LAZER_DIRECTION_PIN_1, LOW);
    for (int i = _LAZER_NOW_LAZER_IN_Y; i != TargetY; i--)
    {
      digitalWrite(_LAZER_STEP_PIN_1, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_1, LOW);
      delay(Drspeed);
    }
    analogWrite(_LAZER_ENABLE_PIN_1, 100);
    _LAZER_NOW_LAZER_IN_Y-=_LAZER_NOW_LAZER_IN_Y-TargetY;
  }
}

/*!
Двигает лазер в нужную координату с определенной скоростью.
------------------------------------------
Возможные направления:
\code
 1   2
  \ /
   O
  / \
 4   3
\endcode
\param corn Направление (1, 2, 3, 4)
\param Drspeed Скорость. Значения меньше 1 на свой страх и риск!
*/
void GoToCorner(int corn, int Drspeed)
{
  digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
  digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
  switch(corn)
  {
    case 1:
      digitalWrite(_LAZER_DIRECTION_PIN_1, HIGH);
      digitalWrite(_LAZER_DIRECTION_PIN_2, LOW);
      digitalWrite(_LAZER_STEP_PIN_1, HIGH);
      digitalWrite(_LAZER_STEP_PIN_2, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_1, LOW);
      digitalWrite(_LAZER_STEP_PIN_2, LOW);
      delay(Drspeed);
      _LAZER_NOW_LAZER_IN_X--;
      _LAZER_NOW_LAZER_IN_Y++;
    break;
    case 2:
      digitalWrite(_LAZER_DIRECTION_PIN_1, HIGH);
      digitalWrite(_LAZER_DIRECTION_PIN_2, HIGH);
      digitalWrite(_LAZER_STEP_PIN_1, HIGH);
      digitalWrite(_LAZER_STEP_PIN_2, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_1, LOW);
      digitalWrite(_LAZER_STEP_PIN_2, LOW);
      delay(Drspeed);
      _LAZER_NOW_LAZER_IN_X++;
      _LAZER_NOW_LAZER_IN_Y++;
    break;
    case 3:
      digitalWrite(_LAZER_DIRECTION_PIN_1, LOW);
      digitalWrite(_LAZER_DIRECTION_PIN_2, HIGH);
      digitalWrite(_LAZER_STEP_PIN_1, HIGH);
      digitalWrite(_LAZER_STEP_PIN_2, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_1, LOW);
      digitalWrite(_LAZER_STEP_PIN_2, LOW);
      delay(Drspeed);
      _LAZER_NOW_LAZER_IN_X++;
      _LAZER_NOW_LAZER_IN_Y--;
    break;
    case 4:
      digitalWrite(_LAZER_DIRECTION_PIN_1, LOW);
      digitalWrite(_LAZER_DIRECTION_PIN_2, LOW);
      digitalWrite(_LAZER_STEP_PIN_1, HIGH);
      digitalWrite(_LAZER_STEP_PIN_2, HIGH);
      delay(Drspeed);
      digitalWrite(_LAZER_STEP_PIN_1, LOW);
      digitalWrite(_LAZER_STEP_PIN_2, LOW);
      delay(Drspeed);
      _LAZER_NOW_LAZER_IN_X--;
      _LAZER_NOW_LAZER_IN_Y--;
    break;
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100);
  analogWrite(_LAZER_ENABLE_PIN_2, 100);
}
/*! @} */

/*! \defgroup Numbers Рисование чего то подобного на арабские цифры
    \brief С помощью этих функций можно нарисовать чиселки!
    Координаты начинаются с нижнего левого угла.
    @{
*/
/*!
Двигает лазер так, что получается 1.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber1(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+2, 1);
  SetLazer(1);
  GoToCorner(2, 1);
  GoToCorner(2, 1);
  SetLazerPos(StartX+2, StartY+0, 1);
}

/*!
Двигает лазер так, что получается 2.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber2(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+3, 1);
  SetLazer(1);
  GoToCorner(2, 1);
  GoToCorner(3, 1);
  GoToCorner(4, 1);
  GoToCorner(4, 1);
  SetLazerPos(StartX+0, StartY+1, 1);
  SetLazerPos(StartX+2, StartY+2, 1);
}

/*!
Двигает лазер так, что получается 3.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber3(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+3, 1);
  SetLazer(1);
  GoToCorner(2, 1);
  GoToCorner(3, 1);
  GoToCorner(4, 1);
  GoToCorner(3, 1);
  GoToCorner(4, 1);
  GoToCorner(1, 1);
}

/*!
Двигает лазер так, что получается 4.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber4(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+4, 1);
  SetLazer(1);
  SetLazerPos(StartX+0, StartY+2, 1);
  SetLazerPos(StartX+2, StartY+2, 1);
  SetLazer(0);
  SetLazerPos(StartX+2, StartY+4, 1);
  SetLazer(1);
  SetLazerPos(StartX+2, StartY+0, 1);
}

/*!
Двигает лазер так, что получается 5.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber5(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+2, StartY+4, 1);
  SetLazer(1);
  SetLazerPos(StartX+0, StartY+4, 1);
  SetLazerPos(StartX+0, StartY+2, 1);
  SetLazerPos(StartX+2, StartY+2, 1); 
  SetLazerPos(StartX+2, StartY+0, 1); 
  SetLazerPos(StartX+0, StartY+0, 1);
}

/*!
Двигает лазер так, что получается 6.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber6(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+2, StartY+4, 1);
  SetLazer(1);
  SetLazerPos(StartX+0, StartY+4, 1);
  SetLazerPos(StartX+0, StartY+2, 1);
  SetLazerPos(StartX+2, StartY+2, 1); 
  SetLazerPos(StartX+2, StartY+0, 1); 
  SetLazerPos(StartX+0, StartY+0, 1); 
  SetLazerPos(StartX+0, StartY+2, 1);
}

/*!
Двигает лазер так, что получается 7.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber7(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+4, 1);
  SetLazer(1);
  SetLazerPos(StartX+2, StartY+4, 1);
  SetLazerPos(StartX+2, StartY+2, 1);
  SetLazerPos(StartX+2, StartY+2, 1);
  SetLazerPos(StartX+0, StartY+0, 1);
}

/*!
Двигает лазер так, что получается 8.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber8(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+0, 1);
  SetLazer(1);
  SetLazerPos(StartX+0, StartY+2, 1);
  SetLazerPos(StartX+2, StartY+2, 1);
  SetLazerPos(StartX+2, StartY+4, 1); 
  SetLazerPos(StartX+0, StartY+4, 1); 
  SetLazerPos(StartX+0, StartY+2, 1);
  SetLazer(0); 
  SetLazerPos(StartX+2, StartY+2, 1);
  SetLazer(1);
  SetLazerPos(StartX+2, StartY+0, 1);
  SetLazerPos(StartX+0, StartY+0, 1);
}

/*!
Двигает лазер так, что получается 9.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber9(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+0, 1);
  SetLazer(1);
  SetLazerPos(StartX+2, StartY+0, 1);
  SetLazerPos(StartX+2, StartY+4, 1);
  SetLazerPos(StartX+0, StartY+4, 1); 
  SetLazerPos(StartX+0, StartY+2, 1); 
  SetLazerPos(StartX+2, StartY+2, 1);
}

/*!
Двигает лазер так, что получается 0.
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber0(int StartX=5, int StartY=5)
{
  SetLazer(0);
  SetLazerPos(StartX+0, StartY+0, 1);
  SetLazer(1);
  SetLazerPos(StartX+0, StartY+4, 1);
  SetLazerPos(StartX+2, StartY+4, 1);
  SetLazerPos(StartX+2, StartY+0, 1); 
  SetLazerPos(StartX+0, StartY+0, 1);
}

/*!
Двигает лазер так, что получается Num.
\param Num От 0 до 9
\param StartX Координата по оси X
\param StartY Координата по оси Y
*/
void DrawNumber(int Num, int StartX=5, int StartY=5)
{
  switch(Num)
  {
    case 0:
    DrawNumber0(StartX, StartY);
    break;
    case 1:
    DrawNumber1(StartX, StartY);
    break;
    case 2:
    DrawNumber2(StartX, StartY);
    break;
    case 3:
    DrawNumber3(StartX, StartY);
    break;
    case 4:
    DrawNumber4(StartX, StartY);
    break;
    case 5:
    DrawNumber5(StartX, StartY);
    break;
    case 6:
    DrawNumber6(StartX, StartY);
    break;
    case 7:
    DrawNumber7(StartX, StartY);
    break;
    case 8:
    DrawNumber8(StartX, StartY);
    break;
    case 9:
    DrawNumber9(StartX, StartY);
    break;
  }
}
/*! @} */

/*! \defgroup Imgs Функции для демо-рисования
    \brief С помощью этих функций можно проверить калибровку и шаговики.
    @{
*/

/*!
Двигает лазер так, что получается логотип GitHub.
\param Speed Скорость отрисовки
\image html GitHubDrawing.jpg "My GitHub" width=200cm
*/
void DrawGitHubLogo(int Speed)
{
  SetLazerPos( 4,  0, Speed);
  SetLazerPos( 3,  0, Speed);
  GoToCorner(1, Speed);
  GoToCorner(1, Speed);
  GoToCorner(1, Speed);
  SetLazerPos( 0,  7, Speed);
  GoToCorner(2, Speed);
  GoToCorner(2, Speed);
  GoToCorner(2, Speed);
  SetLazerPos( 7, 10, Speed);
  GoToCorner(3, Speed);
  GoToCorner(3, Speed);
  GoToCorner(3, Speed);
  SetLazerPos(10,  3, Speed);
  GoToCorner(4, Speed);
  GoToCorner(4, Speed);
  GoToCorner(4, Speed);
  SetLazerPos( 6,  0, Speed);
  SetLazerPos( 6,  4, Speed);
  delay(3);
  GoToCorner(2, Speed);
  GoToCorner(2, Speed);
  GoToCorner(1, Speed);
  SetLazerPos( 7,  9, Speed);
  GoToCorner(4, Speed);
  SetLazerPos( 4,  8, Speed);
  GoToCorner(1, Speed);
  SetLazerPos( 3,  7, Speed);
  GoToCorner(4, Speed);
  GoToCorner(3, Speed);
  GoToCorner(3, Speed);
  SetLazerPos( 4,  2, Speed);
  GoToCorner(1, Speed);
  SetLazerPos( 2,  3, Speed);
  GoToCorner(3, Speed);
  GoToCorner(3, Speed);
}

/*!
Рисует квадрат по координатам.
\param StartX Начальная координата по оси X
\param StartY Начальная координата по оси Y
\param EndX Конечная координата по оси X
\param EndY Конечная координата по оси Y
\param Drspeed Скорость
*/
void DrawSquare(int StartX, int StartY, int EndX, int EndY, float Drspeed)
{
  SetLazerPos(StartX, StartY, Drspeed);
  //Y up
  digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_1, HIGH);
  for (int i = 0; i < EndY-StartY; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_1, HIGH);
    delay(Drspeed);
    digitalWrite(_LAZER_STEP_PIN_1, LOW);
    delay(Drspeed);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100);
  //x right
  digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_2, HIGH);
  for (int i = 0; i < EndX-StartX; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_2, HIGH);
    delay(Drspeed);
    digitalWrite(_LAZER_STEP_PIN_2, LOW);
    delay(Drspeed);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100); //wait
  //y down
  digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_1, LOW);
  for (int i = 0; i < EndY-StartY; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_1, HIGH);
    delay(Drspeed);
    digitalWrite(_LAZER_STEP_PIN_1, LOW);
    delay(Drspeed);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100); //wait
  //x left
  digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_2, LOW);
  for (int i = 0; i < EndX-StartX; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_2, HIGH);
    delay(Drspeed);
    digitalWrite(_LAZER_STEP_PIN_2, LOW);
    delay(Drspeed);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100); //wait
  _LAZER_NOW_LAZER_IN_X = StartX;
  _LAZER_NOW_LAZER_IN_Y = StartY;
}
/*! @} */

/*! \defgroup Start Функции для начала работы
    \brief С помощью этих функций можно откалибровать лазер и указать управляющие пины.
    @{
*/

/*!
Калибрует лазер по ограничителям.
*/
void calebrateLaser()
{
  SetLazer(0);
  delay(500);
  SetLazer(1);
  delay(500);
  SetLazer(0);
  delay(200);
  SetLazer(1);
  delay(200);
  SetLazer(0);
  delay(50);
  SetLazer(1);
  delay(50);
  SetLazer(0);
  delay(20);
  SetLazer(1);
  delay(20);
  SetLazer(0);
  delay(5);
  SetLazer(1);
  delay(5);
  for(int i = 0; i < 250; i++)
  {
    SetLazer(0);
    delay(1);
    SetLazer(1);
    delay(1);
  }
  SetLazer(0);
  //x down
  digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_1, LOW);
  for (int i = 0; i < 25; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_1, HIGH);
    delay(30);
    digitalWrite(_LAZER_STEP_PIN_1, LOW);
    delay(30);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100); //wait
  //y left
  digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_2, LOW);
  for (int i = 0; i < 25; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_2, HIGH);
    delay(30);
    digitalWrite(_LAZER_STEP_PIN_2, LOW);
    delay(30);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100); //wait
  delay(1000);
  
  digitalWrite(_LAZER_ENABLE_PIN_1, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_1, HIGH);
  for (int i = 0; i < 6; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_1, HIGH);
    delay(30);
    digitalWrite(_LAZER_STEP_PIN_1, LOW);
    delay(30);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100);
  digitalWrite(_LAZER_ENABLE_PIN_2, HIGH);
  digitalWrite(_LAZER_DIRECTION_PIN_2, HIGH);
  for (int i = 0; i < 6; ++i)
  {
    digitalWrite(_LAZER_STEP_PIN_2, HIGH);
    delay(30);
    digitalWrite(_LAZER_STEP_PIN_2, LOW);
    delay(30);
  }
  analogWrite(_LAZER_ENABLE_PIN_1, 100);
  digitalWrite(_LAZER_ENABLE_PIN_1, LOW);
  digitalWrite(_LAZER_ENABLE_PIN_2, LOW);
  _LAZER_NOW_LAZER_IN_X = 0;
  _LAZER_NOW_LAZER_IN_Y = 0;
  SetLazer(1);
}

/*!
Устанавливает пины для шаговиков и лазера.
\param StepPin1
\param DirectionPin1
\param EnablePin1
\param StepPin2
\param DirectionPin2
\param EnablePin2
\param ControllPin1
*/
void LazerInit(int StepPin1, int DirectionPin1, int EnablePin1, int StepPin2, int DirectionPin2, int EnablePin2, int ControllPin1)
{
  _LAZER_STEP_PIN_1 = StepPin1;
  _LAZER_DIRECTION_PIN_1 = DirectionPin1;
  _LAZER_ENABLE_PIN_1 = EnablePin1;
  _LAZER_STEP_PIN_2 = StepPin2;
  _LAZER_DIRECTION_PIN_2 = DirectionPin2;
  _LAZER_ENABLE_PIN_2 = EnablePin2;
  _LAZER_CONTROLL_PIN_1 = ControllPin1;
  pinMode(_LAZER_STEP_PIN_1, OUTPUT);
  pinMode(_LAZER_DIRECTION_PIN_1, OUTPUT);
  pinMode(_LAZER_ENABLE_PIN_1, OUTPUT);
  pinMode(_LAZER_STEP_PIN_2, OUTPUT);
  pinMode(_LAZER_DIRECTION_PIN_2, OUTPUT);
  pinMode(_LAZER_ENABLE_PIN_2, OUTPUT);
  pinMode(_LAZER_CONTROLL_PIN_1, OUTPUT);
  calebrateLaser();
}
/*! @} */
