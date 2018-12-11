# Inorganic Chemistry Knowledge Base
База знаний проекта по химии "0-zone"

### Содержание  
1. [Инструкция по созданию своей копии базы](#instruction)
2. [Установка системы](#installing)
3. [Запуск системы](#start)
4. [Клонирование базы (ТОЛЬКО НА ПУСТОЙ OSTIS)](#emptycloning)
4. [Клонирование базы (rebase)](#cloning)
5. [Отправка изменений (с ветки master)](#pushing)
6. [Получение изменений (merge)](#pulling)
6. [Получение изменений (rebase)](#rebasing)
7. [Основные ссылки](#links)
8. [TODO файл](#todo)
9. [Краткая информация о содержимом](#content)

### <a name="instruction"></a> Инструкция по созданию своей копии базы
- Форкнуть себе репозиторий (вверху есть кнопка Fork)

### <a name="installing"></a> Установка системы
Установка осуществляется с системы ubuntu через терминал
```sh
$ git clone https://github.com/ShunkevichDV/ostis [название папки]
```
Если не ввести название папки, то она будет называться ostis
```sh
$ cd [название папки]/scripts
$ ./prepare.sh
```
Если что-то спросит, то соглашаемся, вводим пароль, когда запросит и т.д.

### <a name="start"></a> Запуск системы
Открываем терминал
```sh
$ cd [название папки]/scripts
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

### <a name="emptycloning"></a> Клонирование базы (ТОЛЬКО НА ПУСТОЙ OSTIS)
Открываем терминал
```sh
$ cd [название папки]
```
ВНИМАНИЕ!!! Следующая команда удалит папку kb (совсем, полностью, без возможности восстановления, но вы и так должны это знать)
```sh
$ rm -f -R  kb
$ git clone [ссылка на Вашу копию репозитория] kb
$ cd kb
$ git remote add mainRepository https://github.com/Maribo27/chemistry_kb
$ git fetch mainRepository
$ git checkout -b main mainRepository/master
$ git checkout master
```

### <a name="cloning"></a> Клонирование базы (НЕ ПРОВЕРЕНО)
Открываем терминал
```sh
$ cd [название папки]/kb
$ git init
$ git remote add origin [ссылка на Вашу копию репозитория]
$ git add --all
$ git commit -m "Your commit"
$ git fetch
$ git rebase origin/master
```
В случае, если вы не хотели коммитить предыдущие изменения, то можно прописать следующую команду
```sh
$ git reset origin/master
```
Она откатит коммит
```sh
$ git remote add mainRepository https://github.com/Maribo27/chemistry_kb
$ git fetch mainRepository
$ git checkout -b main mainRepository/master
$ git checkout master
```

### <a name="pushing"></a> Отправка изменений (с ветки master)
- Закоммитить и залить на свой репозиторий локальные изменения
```sh
$ git checkout master
$ git add --all
$ git commit -m "commit description"
$ git push
```
- Настоятельно рекомендую ознакомиться с [данной](https://htmlacademy.ru/blog/27-how-to-squash-commits-and-why-it-is-needed) статьёй: много маленьких коммитов это, конечно, хорошо, но склеивайте хотя бы такие коммиты, как:
> Merge pull request
> Merge remote-tracking branch 'upstream/master' 
- Создать пуллреквест c комментарием в формате: 
> [Имя Фамилия] Комментарий.
- Отметить в [Trello]

### <a name="pulling"></a> Получение изменений (1 способ)
- Изменения на ветке master должны быть закомичены и, желательно, приняты мной
```sh
$ git checkout main
$ git pull
$ git checkout master
$ git merge main
```

### <a name="rebasing"></a> Получение изменений (2 способ, НЕ ПРОВЕРЕНО)
```sh
$ git checkout master
$ git fetch
$ git rebase main/master
```

### <a name="links"></a> Основные ссылки
- [Google Doc] - у каждого курса свой лист
- [Trello]

### <a name="todo"></a> TODO файл
Если берете файлы на формализацию, из этого списка, то помечаете это в гугл доке и на трелло и отписываете [мне](https://vk.com/id8930868)

### <a name="content"></a> Краткая информация о содержимом
- Agents - папка с агентами
    - Proc - процедуры, используемые в агентах
    - Test - тестовые примеры для запуска агентов (вещества и др.)
- Concepts - папка с понятиями (все понятия нужно переместить в разделы и удалить)
- Elements - папка с химическими элементами (все элементы нужно переместить в соответствующие разделы и удалить)
- Sections - декомпозиция базы
- Additional - папка с понятиями, которые не относятся к основным разделам
    - Const - химические константы
	- Parameters - параметры (степени окисления, группы, периоды, числа)
	- minerals.scs - минералы
	- other.scs - понятия, которых нет в базе, но есть идентификатор
- Menu - элементы меню (вопросы, агенты)
    - ui_view_kb_chemistry/lib_ui_menu_na_kb_chemistry.scs - список команд для химии
    - ui_view_kb_chemistry/ui_menu_na_view_kb_chemistry.scsi - список команд для химии (сюда добавляются агенты)
    - table.html - периодическая таблица
    - ui_main_menu.scs - хедер страниц
    - ui_menu_na_keynodes.scs - ключевые узлы (менять не нужно)
    - ui_menu_run_scp_program.scs - запуск scp-программы (для лабораторных работ)
- Substances - папка с химическими веществами (все вещества нужно переместить в соответствующие разделы и удалить)
- Reactions - химические реакции на scl
- Ui_components - графические компоненты
    - src/build_components.py - скрипт для сборки компонентов (менять не нужно)
    - src/components/[имя компонента]/src/[имя компонента]-common.js - прототип компонента
    - src/components/[имя компонента]/src/[имя компонента]-component.js - главное окно
    - src/components/[имя компонента]/src/[имя компонента]-paintPanel.js - логика компонента
    - src/components/[имя компонента]/static - сгенерированный компонент
    - src/components/[имя компонента]/build.json - описание используемых js файлов в компоненте
    - components.scs - описание компонентов
    - format.scs - описание форматов для компонентов
    - update_[название компонента].sh - скрипт для обновления конкретного компонента
    - update_components.sh - скрипт для обновления всех компонентов (менять не нужно)
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
