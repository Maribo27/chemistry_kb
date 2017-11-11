# Inorganic Chemistry Knoledge Base
База знаний проекта по химии "0-zone"

### Инструкция по созданию своей копии базы
- Форкнуть себе репозиторий (вверху есть кнопка Fork)

### Установка системы
Установка осуществляется с системы ubuntu через терминал
```sh
$ git clone https://github.com/ShunkevichDV/ostis здесьМожноВвестиСвоеНазваниеДляПапкиСистемы
```
Если не ввести название папки, то она будет называться ostis
```sh
$ cd ostis/scripts
$ ./prepare.sh
```
Если что-то спросит, то соглашаемся, вводим пароль, когда запросит и т.д.

### Запуск системы
Открываем терминал
```sh
$ cd ostis/scripts
$ ./restart_sctp.sh
```
Открываем новую вкладку (CTRL + SHIFT + T)
```sh
$ ./run_scweb.sh
```
Открываем браузер и вводим адрес
```sh
localhost:8000
```

### Клонирование базы
Открываем терминал
```sh
$ cd ostis
$ rm -f -R  kb
$ git clone ссылкаНаВашуКопиюРепозитория kb
$ cd kb
$ git remote add mainRepository https://github.com/Maribo27/chemistry_kb
$ git fetch mainRepository
$ git checkout -b main mainRepository/master
$ git checkout master

```

### Отправка изменений (с ветки master)
- Закоммитить и залить на свой репозиторий локальные изменения
```sh
$ git add --all
$ git commit -m "commit description"
$ git push
```
- Создать пуллреквест (кнопка New Pull Request)
- Отметить в [Trello]

### Получение изменений
- Изменения на ветке master должны быть закомичены и, желательно, приняты мной
```sh
$ git checkout main
$ git pull
$ git checkout master
$ git merge main
```

### Основные ссылки
- [Google Doc] - у каждого курса свой лист
- [Trello]

### TODO файл
Если берете файлы на формализацию, из этого списка, то помечаете это в гугл доке и на трелло и отписываете [мне](https://vk.com/id8930868)

### Краткая информация о содержимом
- Agents - папка с агентами
- Concepts - папка с понятиями (все понятия нужно переместить в разделы и удалить)
- Elements - папка с химическими элементами
- Sections - декомпозиция базы
- Additional - папка с понятиями, которые не относятся к основным разделам
    - Agents - файлы, необходимые для агентов, но неотносящиеся к системе
	- Parameters - параметры (степени окисления, группы, периоды, числа)
- menu - элементы меню (вопросы, агенты)
- Substances - папка с химическими веществами
- [README.md](https://github.com/Maribo27/chemistry_kb/blob/master/README.md) - read me файл
- TODO - понятия, которых нет в базе, но на них есть ссылки
- concepts.scs - абсолютные понятия и идентификаторы, которых нет в базе, но на них есть ссылки (если берете их на формализацию, то помечаете это в гугл доке и на трелло)
- nrels.scs - относительные понятия и идентификаторы, которых нет в базе, но на них есть ссылки (если берете их на формализацию, то помечаете это в гугл доке и на трелло)
- rrels.scs - ролевые понятия и идентификаторы, которых нет в базе, но на них есть ссылки (если берете их на формализацию, то помечаете это в гугл доке и на трелло)

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [Google Doc]: <https://docs.google.com/spreadsheets/d/1DVwCNw2nb2aefu-T6yScImUMZA8cTb8-BI2HRelRXDs>
   [Trello]: <https://trello.com/b/KkpDPDcI/%D1%85%D0%B8%D0%BC%D0%B8%D1%8F>
   [OSTIS]: <https://github.com/ShunkevichDV/ostis>
   [База Знаний IMS]: <https://github.com/ShunkevichDV/ims.ostis.kb>
