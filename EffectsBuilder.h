#ifndef EFFECTSBUILDER_H
#define EFFECTSBUILDER_H
#include <QWidget>
class QComboBox;
class QCheckBox;
class QPushButton;
class QFrame;
class QLabel;
class Effect;
class SmilesSelector;
class QLineEdit;
class QTextEdit;
class EffectsBuilder: public QWidget{
	Q_OBJECT
private:
	Effect* EffectPreview;
	QFrame* Background;
	QComboBox* EffectTypeCombo;
	QCheckBox* ManaEffectCheck;
	QCheckBox* DoesntStackCheck;
	QCheckBox* HiddenEffectCheck;
	QLabel* TriggersLabel;
	QComboBox* AddTriggerCombo;
	QPushButton* ResetTriggersButton;
	QComboBox* AddCostCombo;
	QPushButton* ResetCostButton;
	QLineEdit* EffectNameEdit;
	QTextEdit* EffectTextEditor;
	QPushButton* SymbolsMenuButton;
	SmilesSelector* SymbolsSelector;
public:
	EffectsBuilder(QWidget* parent=0);
protected:
	void resizeEvent(QResizeEvent* event);
private slots:
	void SetEffectText();
	void SetEffectType(int index);
	void ResetTriggers();
	void ResetCost();
	void AddTrigger(int index);
	void AddCost(int index);
	void AddSymbol(int index);
	void SetManaEffect();
	void SetDoesntStack();
	void SetHiddenEffect();
};
#endif