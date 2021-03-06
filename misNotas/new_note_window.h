#ifndef NEW_NOTE_WINDOW_H
#define NEW_NOTE_WINDOW_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

namespace Ui {
class new_note_window;
}

class new_note_window : public QWidget {
    Q_OBJECT
public:
    explicit new_note_window(QWidget* parent = nullptr);
    ~new_note_window();
private slots:
    void create();
private:
    Ui::new_note_window* ui;
};

#endif // NEW_NOTE_WINDOW_H
