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

        double getEdgeWeight() const;
        double getEdgeImportance() const;
        double getEdgeSurvivalRate() const;
};

#endif // EDITEDGEDIALOG_H
