Программа IPC "Лифт"
Для запуска нужно задать в качестве параметров запускаемой функции 
argv[1] -- первый параметр -- время проводимое пассажиром в лифте
argv[2] -- второй параметр -- вес каждого пассажира
Лифт может перевозить 500 кг
Каждую секунду в лифт заходит новый пассажир
Количество процессов на экране консоли "равно" количеству пассажиров
Semaphore value -- это количество свободного места в лифте
Если задать достаточно большие вес и время, то лифт не будет справляться и количество процессов будет постоянно расти до нажатия crtl-C или до заполнения памяти (не рекомендуется)