#include "texttoolbar.h"
#include <QAction>

TextToolbar::TextToolbar(QWidget *parent) :
    QToolBar(parent),
    action_clear(new QAction(QIcon::fromTheme("edit-clear"), tr("Clear"), this)),
    action_copy(new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this)),
    action_pronounce(new QAction(QIcon::fromTheme("media-playback-start"), tr("Play"), this))
{
    addAction(action_clear);
    addAction(action_copy);
    addAction(action_pronounce);

    connect(action_clear, SIGNAL(triggered()), SIGNAL(requestClear()));
    connect(action_copy, SIGNAL(triggered()), SIGNAL(requestCopy()));
    connect(action_pronounce, SIGNAL(triggered()), SIGNAL(requestPronounce()));

    setIconSize(QSize(16, 16));
}