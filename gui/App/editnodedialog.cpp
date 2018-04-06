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
    m_quantitySpinBox = new QSpinBox;
    m_birthRateSpinBox = new QDoubleSpinBox;

    QFormLayout* layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Image filepath :")), m_filepathLineEdit);
    layout->addRow(new QLabel(tr("Quantity :")), m_quantitySpinBox);
    layout->addRow(new QLabel(tr("Birth Rate :")), m_birthRateSpinBox);
    m_quantitySpinBox->setMaximum(1000);
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
    NodeAttr* attr = (NodeAttr*) m_gnode->m_node->getData();
    NodeGuiAttr* gui = attr->m_gui;
    if(gui!=nullptr){
        m_filepathLineEdit->setText(QString::fromStdString(gui->m_imageFilepath));
    }
    if(attr!=nullptr){
        m_quantitySpinBox->setValue(attr->m_quantity);
        m_birthRateSpinBox->setValue(attr->m_birthRate);
    }
}

QString EditNodeDialog::getNodeImageFilepath() const{
    return m_filepathLineEdit->text();
}

int EditNodeDialog::getNodeQuantity() const{
    return m_quantitySpinBox->value();
}

double EditNodeDialog::getNodeBirthRate() const{
    return m_birthRateSpinBox->value();
}
