#include "editedgedialog.h"

EditEdgeDialog::EditEdgeDialog(Edge* edge) : QDialog()
{
    m_edge = edge;
    createFormGroupBox();
    createButtonBox();
    createMainLayout();
    initView();
}

void EditEdgeDialog::createFormGroupBox(){
    m_formGroupBox = new QGroupBox(tr("Edge information"));
    m_survivalRateSpinBox = new QDoubleSpinBox;
    m_importanceSpinBox = new QDoubleSpinBox;
    m_weightSpinBox = new QDoubleSpinBox;

    QFormLayout* layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Weigth :")), m_weightSpinBox);
    layout->addRow(new QLabel(tr("Importance :")), m_importanceSpinBox);
    layout->addRow(new QLabel(tr("Survival Rate :")), m_survivalRateSpinBox);
    m_formGroupBox->setLayout(layout);
}

void EditEdgeDialog::createButtonBox(){
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void EditEdgeDialog::createMainLayout(){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_formGroupBox);
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Edit Edge"));
}

void EditEdgeDialog::initView(){
    EdgeAttr* attr = (EdgeAttr*) m_edge->getData();
    if(attr==nullptr){
        attr = new EdgeAttr();
        m_edge->setData(attr);
    }

    m_weightSpinBox->setValue(m_edge->getWeight());
    m_importanceSpinBox->setValue(attr->m_importance);
    m_survivalRateSpinBox->setValue(attr->m_survivalRate);
}

double EditEdgeDialog::getEdgeWeight() const{
    return m_weightSpinBox->value();
}

double EditEdgeDialog::getEdgeImportance() const{
    return m_importanceSpinBox->value();
}

double EditEdgeDialog::getEdgeSurvivalRate() const{
    return m_survivalRateSpinBox->value();
}
