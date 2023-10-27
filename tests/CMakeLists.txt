file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp") #Добавляем в переменную srcs все файлы с расширением .cpp

add_executable(${test} ${srcs} ${hdrs})

target_link_libraries(${test} ${testLib} ${include}) #Подключаем к проекту с именем ${test} библиотеку с именем ${testLib}
