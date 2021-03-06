#include "audionoteform.h"
#include "ui_audionoteform.h"

AudioNoteForm::AudioNoteForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AudioNoteForm)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    this->setFixedSize(640, 480);
    ui->play_button->setText("Play");
    player = new QMediaPlayer;
    ui->volumeControl->setValue(50);
    connect(ui->positionSlider, &QSlider::sliderMoved, this, &AudioNoteForm::setPosition);
    connect(ui->volumeControl, &QSlider::sliderMoved, this, &AudioNoteForm::volume_slider_move);
    connect(ui->open_button, &QPushButton::clicked, this, &AudioNoteForm::open);
    connect(ui->saveButton, &QPushButton::clicked, this, &AudioNoteForm::save);
    connect(ui->play_button, &QPushButton::clicked, this, &AudioNoteForm::play);
    connect(player, &QMediaPlayer::stateChanged, this, &AudioNoteForm::mediaStateChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &AudioNoteForm::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &AudioNoteForm::durationChanged);
}

AudioNoteForm::~AudioNoteForm()
{
    delete ui;
    if (player->state() == QMediaPlayer::StoppedState)
        player->stop();
    delete player;
}

void AudioNoteForm::play()
{
    if (player->state() == QMediaPlayer::StoppedState) {
        player->setMedia(QUrl::fromLocalFile(note->get_file_path()));
        player->setVolume(ui->volumeControl->value());
        player->play();
    } else {
        player->stop();
    }
}

void AudioNoteForm::transfer_note(Note* n)
{
    note = dynamic_cast<AudioNote*>(n);
}

void AudioNoteForm::open()
{
    QString file_name = QFileDialog::getOpenFileName();
    note->load_data_from_file(file_name);
}

void AudioNoteForm::volume_slider_move(int position)
{
    player->setVolume(position);
}

void AudioNoteForm::save()
{
    note->save_into_file();
}

void AudioNoteForm::positionChanged(qint64 position)
{
    ui->positionSlider->setValue(position);
}

void AudioNoteForm::durationChanged(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
}

void AudioNoteForm::setPosition(int position)
{
    player->setPosition(position);
}

void AudioNoteForm::mediaStateChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->play_button->setText("Pause");
        break;
    default:
        ui->play_button->setText("Play");
        break;
    }
}
