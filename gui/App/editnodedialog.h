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

/**
 * @brief Popup qui permet de modifier les attributs d'un GNode
 */
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

        /**
         * @brief Retourne la valeur contenue dans le champs "filepath"
         * @return le filepath
         */
        QString getNodeImageFilepath() const;

        /**
         * @brief Retourne la valeur contenue dans le champs "quantity"
         * @return la quantity
         */
        int getNodeQuantity() const;

        /**
         * @brief Retourne la valeur contenue dans le champs "birth rate"
         * @return le birth rate
         */
        double getNodeBirthRate() const;
};

#endif // EDITNODEDIALOG_H
