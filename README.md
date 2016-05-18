# homework

Тестовое задание по С++	

Необходимо написать приложение клиент-сервер для двух хостов:
- Серверная часть получает от клиентской натуральные числа и делает для каждого из них разложение на простые множители.
- Клиентская часть посылает случайные натуральные числа в произлольные моменты времени на серверную часть.

Задача должна быть реализована на С++.
Выбор операционных систем, их версий, сторонних библиотек и технических решений необходимо сделать самостоятельно и обосновать.

Выбор операционных систем:
Сервер и клиент будут работать на Mac OS, по следующим причинам:
- у меня дома нет Windows, а по RDP или на виртуальной машине работать неудобно;
- никогда не писал под Mac OS, будет новый опыт;

На мой взгляд реализовать серверную часть будет удобно в виде REST сервсиса.
Для этого выбрана кроссплатформенная библиотека на C++ POCO, в ней есть веб сервер, который просто использовать.
Для данной задачи эта библиотека слишком тяжела,  однако я ее попробую скомпилировать без лишних зависимотей, типа ssl.

Http клиент будет написан самостоятельно, без использования сторонних библиотек. 

Компиляция POCO c поддержкой С++11 и libc++:
make clean
./configure --static --minimal --config=Darwin64-clang-libc++ --poquito --no-tests --no-samples --no-sharedlibs
make