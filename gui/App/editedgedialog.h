#ifndef EDITEDGEDIALOG_H
#define EDITEDGEDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>

#include "../../entities/graph/include/Edge.h"
#include "../../entities/data/include/EdgeAttr.h"

/**
 * @brief Popup qui permet de modifier les attributs d'un Edge
 */
class EditEdgeDialog : public QDialog
{
    private:
        Edge* m_edge;

        // box
        QGroupBox* m_formGroupBox;
        QDialogButtonBox* m_buttonBox;

        // fields
        QDoubleSpinBox* m_importanceSpinBox;
        QDoubleSpinBox* m_survivalRateSpinBox;
        QDoubleSpinBox* m_weightSpinBox;

        void createFormGroupBox();
        void createButtonBox();
        void createMainLayout();
        void initView();

    public:
        EditEdgeDialog(Edge* edge);

        /**
         * @brief Retourne la valeur contenue dans le champ "weight"
         * @return le poids
         */
        double getEdgeWeight() const;

        /**
         * @brief Retourne la valeur contenue dans le champ "importance"
         * @return l'importance
         */
        double getEdgeImportance() const;

        /**
         * @brief Retourne la valeur contenue dans le champs "survival rate"
         * @return le survival rate
         */
        double getEdgeSurvivalRate() const;
};

#endif // EDITEDGEDIALOG_H
