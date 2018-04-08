#ifndef EDITNODEDIALOG_H
#define EDITNODEDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>

#include "gnode.h"

class EditNodeDialog : public QDialog
{
    Q_OBJECT

    private:
        GNode* m_gnode;

        // box
        QGroupBox* m_formGroupBox;
        QDialogButtonBox* m_buttonBox;

        // fields
        QLineEdit* m_filepathLineEdit;
        QSpinBox* m_quantitySpinBox;
        QDoubleSpinBox* m_birthRateSpinBox;

        void createFormGroupBox();
        void createButtonBox();
        void createMainLayout();
        void initView();

    public:
        EditNodeDialog(GNode* gnode);

        QString getNodeImageFilepath() const;
        int getNodeQuantity() const;
        double getNodeBirthRate() const;
};

#endif // EDITNODEDIALOG_H
