# Курсова Работа ООП-1част ТУ-Варна C++ 
I. Да се състави клас Книга

Скрити член променливи:  Име на книга- string; Автор – string; Заета/свободна – bool

Публични функции: 
1.  Конструктори - експлицитен (име), експлицитен (име, флаг – заета/свободна);
2.	Заемане на книгата: TakeBook() 
3.	Връщане на книга: ReturnBook() 
4.	Четене/запис 
5.	Operator == сравнява по всички данни 
6.	Operator< за сравнение за по-малко на подадения параметър обект с текущия по име на книгата 
7.	Преобразува / връща низ от членовете на класа
8.	Operator<< (извежда в указан изходен поток)
9.	Operator>> (чете от указан входен поток) 

II. Да се състави клас Библиотека 

Скрити член променливи: име на библиотеката - string m_strLibName;

брой стелажи; капацитет на стелаж; 

multimap на разположение - двойки (стелаж, книга) – multimap<int,LibraryBook>;

map за търсене буква от име към номер стелаж - двойки (символ,стелаж) - map <char,int>

Публични функции:
1.	Конструктори - експл. Конструктор с име на файл. Формат на файла: 

ИМЕ_НА_БИБЛИОТЕКА<SP>БРОЙ_СТЕЛАЖИ<SP>КАПАЦИТЕТ_НА_СТЕЛАЖ<SP>ИМЕ_НА_КНИГА<SP>АВТОР<SP>ИМЕ_НА_КНИГА<SP>АВТОР<EOF> 

LIBNAME 4 5 BOOK20 AUT20 BOOK12 AUT12 BOOK13 AUT13 BOOK11 AUT11 BOOK3 AUT3

Разпределя книгите по стелажите подреждайки ги по азбучен ред на имената на книгите, създава карта за търсене по буква

2.	По зададен стелаж връща вектор от наличните книги
3.	По зададен стелаж връща вектор от заети книги 
4.	Търси свободна книга по зададено име 
5.	Заема свободна книга по зададено име 
6.	Търси заета книга по зададено име 
7.	Връща книга по зададено име 

III. Главна функция (main) 
1.	Създава обекти Library по експл. Конструктор от файл 
2.	Създава вектор от свободни и заети книги 
3.	Извежда книгите по указан стелаж на конзолен изход 
4.	Заема книга по име, извежда на конзолен изход 
5.	Резултат връща книга, извежда на конзолен изход резултат 
