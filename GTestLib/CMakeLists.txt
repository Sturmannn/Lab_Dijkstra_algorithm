file(GLOB hdrs "*.h*" "*.hpp") #Добавляем в переменную hdrs все файлы с расширением .h .hpp
file(GLOB srcs "*.cpp" "*.cc") #Добавляем в переменную srcs все файлы с расширением .cpp .cc

add_library(${testLib} STATIC ${srcs} ${hdrs}) #Создаем статическую библиотеку с именем из переменной 