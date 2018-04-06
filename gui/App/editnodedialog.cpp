#include "editnodedialog.h"

EditNodeDialog::EditNodeDialog(GNode* gnode) : QDialog()
{
    m_gnode = gnode;
    createFormGroupBox();
    createButtonBox();
    createMainLayout();
    initView();
}

void EditNodeDialog::createFormGroupBox(){
    m_formGroupBox = new QGroupBox(tr("Node information"));
    m_filepathLineEdit = new QLineEdit;
    QFormLayout* layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Image filepath:")), m_filepathLineEdit);
//    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
//    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    m_formGroupBox->setLayout(layout);
}

void EditNodeDialog::createButtonBox(){
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void EditNodeDialog::createMainLayout(){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_formGroupBox);
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Edit Node"));
}

void EditNodeDialog::initView(){
    NodeGuiAttr* gui = m_gnode->m_attr;
    if(gui!=nullptr){
        m_filepathLineEdit->setText(QString::fromStdString(gui->m_imageFilepath));
    }
}

QString EditNodeDialog::getNodeImageFilepath() const{
    return m_filepathLineEdit->text();
}
