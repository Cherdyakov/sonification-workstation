#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *processingLayout = new QVBoxLayout;
    alphaSpinBox = new QSpinBox;
    procComboBox = new QComboBox;

    // Data processing section.
    QLabel *procLabel = new QLabel;
    procLabel->setText("Data smoothing:");
    QLabel *alphaLabel = new QLabel;
    QPixmap pixmap;
    if (!pixmap.load( ":/images/alpha.png" )) {
        qDebug("Failed to load images/target.png");
    }
    alphaLabel->setPixmap(pixmap);
    alphaLabel->setScaledContents(true);
    alphaLabel->setFixedSize(14, 14);

    QHBoxLayout *alphaLayout = new QHBoxLayout;
    alphaLayout->addWidget(alphaLabel);
    alphaLayout->addWidget(alphaSpinBox);

    procComboBox->addItem("None");
    procComboBox->addItem("Simple Average");
    procComboBox->addItem("Exponential Average");
    processingLayout->setContentsMargins(4,4,4,4);
    processingLayout->addWidget(procLabel);
    processingLayout->addWidget(procComboBox);
    processingLayout->addLayout(alphaLayout);

    // Stylesheet.
    this->setObjectName("TrackHeader");
    this->setAutoFillBackground(true);
    alphaSpinBox->setObjectName("AlphaSpinBox");
    procComboBox->setObjectName("ProcComboBox");
    procLabel->setObjectName("ProcLabel");

    // Add everything to main layout.
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(2);
    mainLayout->addLayout(processingLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // connect signals and slots
    connect(procComboBox, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(on_processingChanged(QString)));

}

void TrackHeader::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TrackHeader::on_processingChanged(QString text)
{

}
