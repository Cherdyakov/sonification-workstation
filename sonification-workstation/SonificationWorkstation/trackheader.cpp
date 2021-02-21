#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *processingLayout = new QVBoxLayout;
    nSpinBox_ = new QSpinBox;
    procComboBox_ = new QComboBox;

    // Data processing section.
    QLabel *procLabel = new QLabel;
    procLabel->setText("Data smoothing:");
    QLabel *nuLabel = new QLabel;
    QPixmap pixmap;
    if (!pixmap.load( ":/images/nu.png" )) {
        qDebug("Failed to load images/nu.png");
    }
    nuLabel->setPixmap(pixmap);
    nuLabel->setScaledContents(true);
    nuLabel->setFixedSize(18, 18);

    QHBoxLayout *nuLayout = new QHBoxLayout;
    nuLayout->addWidget(nuLabel);
    nuLayout->addWidget(nSpinBox_);

    procComboBox_->setAccessibleName("Data smoothing dropdown. Selects smoothing applied to data track during playback.");
    procComboBox_->setAccessibleDescription("");
    procComboBox_->addItem("None");
    procComboBox_->addItem("Simple Average");
    procComboBox_->addItem("Exponential Average");
    processingLayout->setContentsMargins(4,4,4,4);
    processingLayout->addWidget(procLabel);
    processingLayout->addWidget(procComboBox_);
    processingLayout->addLayout(nuLayout);

    nSpinBox_->setAccessibleName("Smoothing constant. Sets damping factor for exponential average or window size for simple average.");
    nSpinBox_->setAccessibleDescription("");

    // Stylesheet.
    this->setObjectName("TrackHeader");
    this->setAutoFillBackground(true);
    nSpinBox_->setObjectName("NuSpinBox");
    procComboBox_->setObjectName("ProcComboBox");
    procLabel->setObjectName("ProcLabel");

    // Add everything to main layout.
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(2);
    mainLayout->addLayout(processingLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // connect signals and slots
    connect(procComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TrackHeader::onProcessingTypeChanged);
    connect(nSpinBox_, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &TrackHeader::onNvalChanged);

    // Initialize
    nSpinBox_->setMaximum(2048);
    nSpinBox_->setValue(2);

}

void TrackHeader::setNumber(uint num)
{
    trackNumber_ = num;
}

void TrackHeader::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TrackHeader::onProcessingTypeChanged(int idx)
{
    ENUMS::PROCESSING_TYPE type;
    switch (idx) {
    case 0:
        type = ENUMS::PROCESSING_TYPE::NONE;
        break;
    case 1:
        type = ENUMS::PROCESSING_TYPE::SIMPLE;
        break;
    case 2:
        type = ENUMS::PROCESSING_TYPE::EXPONENTIAL;
        break;
    }
    emit processingTypeChanged(trackNumber_, type);
}

void TrackHeader::onNvalChanged(int n)
{
    emit nValChanged(trackNumber_, n);
}
