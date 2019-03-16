#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *displayLayout = new QHBoxLayout;
    QVBoxLayout *processingLayout = new QVBoxLayout;
    display = new QDoubleSpinBox;
    alphaSpinBox = new QSpinBox;
    procComboBox = new QComboBox;
    QPalette* pal = new QPalette;

    // set background color for header
    pal->setColor(QPalette::Background, QColor("dark grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);

    // data display section
    //    Qlabel *label = new QLabel;
    // set up data display
    display->setReadOnly(true);
    display->setButtonSymbols(QAbstractSpinBox::NoButtons);
    //    label->setText("");
    //    displayLayout->addWidget(label);
    displayLayout->setContentsMargins(4,4,4,4);
    displayLayout->addWidget(display);

    // data processing section
    QLabel *procLabel = new QLabel;
    procLabel->setText("Data processing:");
    QLabel *alphaLabel = new QLabel;
    QPixmap pixmap;
    if (!pixmap.load( ":/images/alpha.png" )) {
        qDebug("Failed to load images/target.png");
    }
    alphaLabel->setPixmap(pixmap);
    alphaLabel->setScaledContents(true);
    alphaLabel->setFixedSize(16, 16);

    QHBoxLayout *alphaLayout = new QHBoxLayout;
    alphaLayout->addWidget(alphaLabel);
    alphaLayout->addWidget(alphaSpinBox);

    procComboBox->addItem("None");
    procComboBox->addItem("Simple Average");
    procComboBox->addItem("Exponential Average");
    procComboBox->addItem("Cumulative Average");
    processingLayout->setContentsMargins(4,4,4,4);
    processingLayout->addWidget(procLabel);
    processingLayout->addWidget(procComboBox);
    processingLayout->addLayout(alphaLayout);

    // add everything to main layout
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(2);
    mainLayout->addLayout(displayLayout);
    mainLayout->addLayout(processingLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // connect signals and slots
    connect(procComboBox, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(on_processingChanged(QString)));

}

void TrackHeader::on_processingChanged(QString text)
{

}
