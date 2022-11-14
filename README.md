# search_engine
## Локальный поисковый движок.
На вход подаются файлы config.json где указываются тексты по которым будет производится поиск по указанным в requests.json запросам.
На выходе в качестве результата выдается answers.json в котором по каждому из запросам список относительных релевантностей каждого из текстов.

## используемые технологии
### nlohmann_json для конвертации в JSON формат  и обратно.
### Библиотека Google Test для осуществления модульного тестирования

### Запуск на локальной машине
1. Скачать проект с github
2. собрать проект
### подготовка к запуску
   1. создать папке с запускаемым exe файлом файл config.json и request.json. За основу можно взять файлы [cmake-build-debug/config.json](https://github.com/Volkivanv/search_engine/blob/b417d6f804d19a90ad45d7e9c2efa56ca1a49713/cmake-build-debug/config.json) и [cmake-build-debug/requests.json](https://github.com/Volkivanv/search_engine/blob/b417d6f804d19a90ad45d7e9c2efa56ca1a49713/cmake-build-debug/requests.json)
   2. в config.json в поле "max_responses" необходимо указать максимальное количество ответов на один запрос.
   3. в config.json в поле files указать пути к файлам по которым будет осуществляться поиск. В качестве примера указаны пути:  
  ##### "files":["resources/file001.txt",
  #####          "resources/file002.txt",
  #####          "resources/file003.txt",
  #####          "resources/file004.txt"]
   3. файл request состоит из списка запросов. Каждый состоит из не более 1 000 слов. Между слов пробелы. 

### работа программы
При запуске программа показывает

 ##### "MySearchEngine" - Название поискового движка из файла config.json:
 ##### "0.1" - Версия. Она должна совпасть с версией приложения. В противном случае будет выдана ошибка.
 ##### 5 - максимальное количество запросов

Далее идет проверка путей файлов:

 ##### "resources/file001.txt" found - означает что file001.txt" по указанному пути найден
 ##### "resources/file003.txt" found - -//-
 ##### "resources/file004.txt" found - -//-
 ##### input command:  result (execute search engine and write answer.json), exit for exit - набор дальнейших команд.
 ##### Caught exception: "resources/file002.txt" File is missing - означает что file002.txt" по указанному пути не найден
 ##### Для продолжения требуется ввести команду result
 ##### программа производит поиск по файлам и составляется файл answer.json в котором находится результат запроса
 ##### В консоль при этом выдается количество найденных результатов по каждому запросу. Это количество текстов в которых ненулевой индекс релевантности и это количество ограничено значением max_responses.
 ##### request001 number of result: 0
 ##### request002 number of result: 1
 ##### request003 number of result: 3
 ##### ..............................

### Результат
Пример результата можно найти в файле https://github.com/Volkivanv/search_engine/blob/855cfe7fc4621823a07a0e4a96027e0fd88b7134/cmake-build-debug/answers.json.
