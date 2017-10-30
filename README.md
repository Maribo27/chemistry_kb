# Inorganic Chemistry Knoledge Base
База знаний проекта по химии "0-zone"

### Установка
- Форкнуть себе репозиторий (вверху есть кнопка Fork)
- Склонировать уже из своего репозитория в папку kb развернутой системы [OSTIS] с заменой (заменить папку menu)
- Создать новую ветку в локальном репозитории
```sh
$ git remote mainRepository https://github.com/Maribo27/chemistry_kb
```
### Отправка изменений
- Закоммитить и залить на свой репозиторий локальные изменения
```sh
$ git add --all
$ git commit -m "commit description"
$ git push
```
- Создать пуллреквест (кнопка New Pull Request)
- Отметить в [Trello]

### Проверка изменений (делать только в том случае, если нет никаких локальных изменений)
- Перейти на ветку с главным репозиторием
```sh
$ git checkout mainRepository
$ git status
```
- Если есть изменения, то скачать их

```sh
$ git pull
$ git checkout [имя основной ветки]
$ git merge mainRepository
```

### Основные ссылки
- [Google Doc] - у каждого курса свой лист
- [Trello]
- [База Знаний IMS]
- [OSTIS]

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

### Установка и запуск системы
Установка осуществляется с системы ubuntu через терминал
```sh
$ git clone https://github.com/ShunkevichDV/ostis [Здесь можно ввести имя для папки, куда клонить]
```
Папка с системой будет называться ostis. После ссылки можно ввести другое имя папки для скачивания, тогда и дальше вместо слова остис прописываем это имя
```sh
$ cd ostis/scripts
$ ./prepare.sh
```
Если что-то спросит, то соглашаемся
```sh
$ ./restart_sctp.sh
```
Открываем новую вкладку (CTRL + SHIFT + T)
```sh
$ cd ostis/scripts
$ ./run_scweb.sh
```
Открываем браузер и вводим адрес
```sh
localhost:8000
```

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [Google Doc]: <https://docs.google.com/spreadsheets/d/1DVwCNw2nb2aefu-T6yScImUMZA8cTb8-BI2HRelRXDs>
   [Trello]: <https://trello.com/b/KkpDPDcI/%D1%85%D0%B8%D0%BC%D0%B8%D1%8F>
   [OSTIS]: <https://github.com/ShunkevichDV/ostis>
   [База Знаний IMS]: <https://github.com/ShunkevichDV/ims.ostis.kb>
