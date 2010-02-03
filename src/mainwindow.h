#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "ui_mainwindow.h"

class Playlist;
class Player;
class Library;
class LibraryConfigDialog;
class RadioModel;
class Song;
class RadioItem;
class OSD;
class TrackSlider;
class EditTagDialog;
class MultiLoadingIndicator;
class SettingsDialog;
class About;

class QSortFilterProxyModel;
class SystemTrayIcon;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void SetHiddenInTray(bool hidden);

 protected:
  void resizeEvent(QResizeEvent* event);
  void closeEvent(QCloseEvent* event);

 private slots:
  void QueueFiles(const QList<QUrl>& urls);
  void FilePathChanged(const QString& path);

  void ReportError(const QString& message);
  void MediaStopped();
  void MediaPaused();
  void MediaPlaying();

  void PlaylistRightClick(const QPoint& global_pos, const QModelIndex& index);
  void PlaylistPlay();
  void PlaylistStopAfter();
  void EditTracks();

  void PlayIndex(const QModelIndex& index);
  void StopAfterCurrent();

  void LibraryDoubleClick(const QModelIndex& index);
  void ClearLibraryFilter();

  void VolumeWheelEvent(int delta);
  void TrayClicked(QSystemTrayIcon::ActivationReason reason);

  void UpdateTrackPosition();

  void RadioDoubleClick(const QModelIndex& index);
  void InsertRadioItem(RadioItem*);
  void ScrobblingEnabledChanged(bool value);
  void Love();

  void LibraryScanStarted();
  void LibraryScanFinished();

 private:
  void SaveGeometry();

 private:
  static const int kStateVersion;
  static const char* kSettingsGroup;

  Ui::MainWindow ui_;
  SystemTrayIcon* tray_icon_;
  OSD* osd_;
  TrackSlider* track_slider_;
  EditTagDialog* edit_tag_dialog_;
  MultiLoadingIndicator* multi_loading_indicator_;
  LibraryConfigDialog* library_config_dialog_;
  About* about_dialog_;

  RadioModel* radio_model_;
  Playlist* playlist_;
  Player* player_;
  Library* library_;

  SettingsDialog* settings_dialog_;

  QMenu* playlist_menu_;
  QAction* playlist_play_pause_;
  QAction* playlist_stop_after_;
  QModelIndex playlist_menu_index_;

  QSortFilterProxyModel* library_sort_model_;

  QTimer* track_position_timer_;
};

#endif // MAINWINDOW_H
