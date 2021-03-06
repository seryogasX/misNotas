#ifndef VIDEONOTEFORM_H
#define VIDEONOTEFORM_H

#include <videonote.h>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QUrl>
#include <QWidget>
#include <QVideoWidget>

namespace Ui {
class VideoNoteForm;
}

class VideoNoteForm : public QWidget {
    Q_OBJECT
public:
    explicit VideoNoteForm(QWidget* parent = nullptr);
    ~VideoNoteForm();
    void get_note(Note*);
    void setUrl(const QUrl& url);
private slots:
    void openFile();
    void play();
    void save();
    void mediaStateChanged(QMediaPlayer::State);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
private:
    Ui::VideoNoteForm* ui;
    VideoNote* note;
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
};

#endif // VIDEONOTEFORM_H
