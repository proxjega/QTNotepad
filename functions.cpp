#include <Qstring>

QString getTitle(QString filename) {
    QString title;
    for (int i = filename.length() - 1; i >= 0; i--) {
        if (filename[i] == '/') {
            title = filename.remove(0, i+1);
            break;
        }
    }
    if(title.isEmpty()) return "Untitled - QTNotepad";
    return title + " - QTNotepad";
}
