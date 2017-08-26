#include "qtaudifier.h"

QtAudifier::QtAudifier(Audifier* item, QObject* parent) : QtSynthItem(parent)
{
    audifier_ = item;
}

SynthItem *QtAudifier::implementation()
{
    return audifier_;
}

void QtAudifier::deleteItem()
{
    audifier_->delete_item();
}

void QtAudifier::addParent(QtSynthItem *parent)
{
    audifier_->add_parent(parent->implementation());
}

void QtAudifier::removeParent(QtSynthItem *parent)
{
    audifier_->remove_parent(parent->implementation());
}

bool QtAudifier::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
{
    return audifier_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtAudifier::removeChild(QtSynthItem *child)
{
    audifier_->remove_child(child->implementation());
}

void QtAudifier::mute(bool mute)
{
    audifier_->mute(mute);
}

void QtAudifier::setAudIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    audifier_->set_aud_indexes(vec);
}

bool QtAudifier::getMute()
{
    bool muted = audifier_->get_mute();
    return muted;
}

QVector<int> QtAudifier::getAudIndexes()
{
    std::vector<int> vec = audifier_->get_aud_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

