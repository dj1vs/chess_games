# All (user and admin) widgets:
- make search qlineedits work
- rename tables header
- manage currentIndex going out of boundaries
- manage multiple qdebug outputs ("Can not find axis on the chart")
- change qspinbox to qlcdnumber or qlineedit
- manage tables and charts resizing
- show messagebox on sql errors
- remove repetitive code in constructors
- group creating a layout and creating widgets to separate functions
# MainWindow
- configure about messagebox
# LoginWidget
- add picture
- login using enter
# Adminwidget and userwidget
- manage resizing (when resizing buttons remain the same and only thing that changes is title qlabel)
# Only user widgets:
- make fields not editable
- write search function
- show messagebox on failed search
# Only admin widgets:
- write completion for foreign keys
- show messagebox when data is saved
### OpeningsStatsWidget
- fix blackWins and draws not showing
- rewrite to qformlayout
- rename altName to altNames
- separate loadtables
- write loadtables querys in separate lines
### ChessGamesListWidget
- add result field
- remove unnecessary qdebug calls
