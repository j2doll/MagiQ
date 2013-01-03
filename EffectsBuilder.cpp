#include "EffectsBuilder.h"
#include "EffectsConstants.h"
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFrame>
#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include "Effect.h"
#include "Smiles Selector.h"
#include <QLineEdit>
#include <QTextEdit>
EffectsBuilder::EffectsBuilder(QWidget* parent)
	:QWidget(parent)
{
	Background=new QFrame(this);
	Background->setObjectName("Background");

	QGroupBox* EffectPreviewGroup=new QGroupBox(this);
	QVBoxLayout* EffectPreviewlayout=new QVBoxLayout(EffectPreviewGroup);
	EffectPreviewGroup->setObjectName("EffectPreviewGroup");
	EffectPreviewGroup->setTitle(tr("Preview"));
	EffectPreview=new Effect(this);
	EffectPreview->setObjectName("EffectPreview");
	EffectPreviewlayout->addWidget(EffectPreview);

	QGroupBox* NameTextGroup=new QGroupBox(this);
	NameTextGroup->setObjectName("NameTextGroup");
	NameTextGroup->setTitle(tr("Name and Text"));
	QGridLayout* NameTextLayout=new QGridLayout(NameTextGroup);
	QLabel* EffectNameLabel=new QLabel(this);
	EffectNameLabel->setObjectName("EffectNameLabel");
	EffectNameLabel->setText(tr("Effect Name"));
	NameTextLayout->addWidget(EffectNameLabel,0,0,1,2);
	EffectNameEdit=new QLineEdit(this);
	EffectNameEdit->setObjectName("EffectNameEdit");
	connect(EffectNameEdit,SIGNAL(textEdited(QString)),EffectPreview,SLOT(SetEffectName(QString)));
	NameTextLayout->addWidget(EffectNameEdit,1,0,1,2);
	QLabel* EffectTextLabel=new QLabel(this);
	EffectTextLabel->setObjectName("EffectTextLabel");
	EffectTextLabel->setText(tr("Effect Text"));
	NameTextLayout->addWidget(EffectTextLabel,2,0);
	SymbolsMenuButton=new QPushButton(this);
	SymbolsMenuButton->setObjectName("SymbolsMenuButton");
	SymbolsMenuButton->setIcon(QIcon(QPixmap(":/Effects/TapBig.png")));
	SymbolsMenuButton->setToolTip(tr("Insert Symbol"));
	NameTextLayout->addWidget(SymbolsMenuButton,2,1);
	SymbolsSelector=new SmilesSelector(this);
	SymbolsSelector->setObjectName("SymbolsSelector");
	connect(SymbolsMenuButton,SIGNAL(clicked()),SymbolsSelector,SLOT(show_toggle()));
	connect(SymbolsSelector,SIGNAL(selected(int)),this,SLOT(AddSymbol(int)));
	EffectTextEditor=new QTextEdit(this);
	EffectTextEditor->setObjectName("EffectTextEditor");
	connect(EffectTextEditor,SIGNAL(textChanged()),this,SLOT(SetEffectText()));
	NameTextLayout->addWidget(EffectTextEditor,3,0,1,2);

	QGroupBox* EffectTypeGroup=new QGroupBox(this);
	QGridLayout* EffectTypelayout=new QGridLayout(EffectTypeGroup);
	EffectTypeGroup->setObjectName("EffectTypeGroup");
	EffectTypeGroup->setTitle(tr("Effect Type"));
	EffectTypeCombo=new QComboBox(this);
	EffectTypeCombo->setObjectName("EffectTypeCombo");
	for (int i=0;i<=EffectsConstants::EffectTypes::OnResolutionEffect;i++){
		EffectTypeCombo->addItem(
			EffectsConstants::EffectTypesNames[i]
			,i);
	}
	connect(EffectTypeCombo,SIGNAL(currentIndexChanged (int)),this,SLOT(SetEffectType(int)));
	EffectTypelayout->addWidget(EffectTypeCombo,0,0,1,2);
	TriggersLabel=new QLabel(this);
	TriggersLabel->setObjectName("TriggersLabel");
	TriggersLabel->setText(tr("Add Trigger"));
	EffectTypelayout->addWidget(TriggersLabel,1,0);
	ResetTriggersButton=new QPushButton(this);
	ResetTriggersButton->setObjectName("ResetTriggersButton");
	ResetTriggersButton->setText("Reset Triggers");
	connect(ResetTriggersButton,SIGNAL(clicked()),this,SLOT(ResetTriggers()));
	EffectTypelayout->addWidget(ResetTriggersButton,2,1);
	AddTriggerCombo=new QComboBox(this);
	AddTriggerCombo->setObjectName("AddTriggerCombo");
	AddTriggerCombo->addItem("",-1);
	for (int i=EffectsConstants::Triggers::EntersTheBattlefield;i<=EffectsConstants::Triggers::Dies;i++){
		QString TextToPrint(EffectsConstants::TriggersNames[i]);
		if (TextToPrint.contains("%1")){
			if (TextToPrint.contains("%2"))
				TextToPrint=TextToPrint.arg(tr("When")).arg(tr("Card"));
		}
		AddTriggerCombo->addItem(
			TextToPrint
			,i);
	}
	connect(AddTriggerCombo,SIGNAL(currentIndexChanged (int)),this,SLOT(AddTrigger(int)));
	EffectTypelayout->addWidget(AddTriggerCombo,2,0);
	TriggersLabel->hide();
	AddTriggerCombo->hide();
	ResetTriggersButton->hide();

	QGroupBox* CostTragetBox=new QGroupBox(this);
	QGridLayout* CostTragetlayout=new QGridLayout(CostTragetBox);
	CostTragetBox->setObjectName("CostTragetBox");
	CostTragetBox->setTitle(tr("Cost and Targets"));
	QLabel* CostLabel=new QLabel(this);
	CostLabel->setObjectName("CostLabel");
	CostLabel->setText(tr("Add Cost"));
	CostTragetlayout->addWidget(CostLabel,0,0);
	ResetCostButton=new QPushButton(this);
	ResetCostButton->setObjectName("ResetCostButton");
	ResetCostButton->setText("Reset Cost");
	connect(ResetCostButton,SIGNAL(clicked()),this,SLOT(ResetCost()));
	CostTragetlayout->addWidget(ResetCostButton,1,1);
	AddCostCombo=new QComboBox(this);
	AddCostCombo->setObjectName("AddCostCombo");
	AddCostCombo->addItem("",-1);
	for (int i=0;i<EffectsConstants::EffectCosts::END;i++){
		QString TextToPrint(EffectsConstants::EffectCostStrings[i]);
		if (TextToPrint.contains("%1")){
			TextToPrint=TextToPrint.arg(1);
		}
		AddCostCombo->addItem(
			TextToPrint
			,i);
	}
	connect(AddCostCombo,SIGNAL(currentIndexChanged (int)),this,SLOT(AddCost(int)));
	CostTragetlayout->addWidget(AddCostCombo,1,0);

	QGroupBox* CheckBoxesGroup=new QGroupBox(this);
	CheckBoxesGroup->setObjectName("CheckBoxesGroup");
	CheckBoxesGroup->setTitle(tr("Effect Properties"));
	ManaEffectCheck=new QCheckBox(this);
	ManaEffectCheck->setObjectName("ManaEffectCheck");
	ManaEffectCheck->setText(tr("Is a Mana Effect"));
	connect(ManaEffectCheck,SIGNAL(stateChanged(int)),this,SLOT(SetManaEffect()));
	DoesntStackCheck=new QCheckBox(this);
	DoesntStackCheck->setObjectName("DoesntStackCheck");
	DoesntStackCheck->setText(tr("Effect resolves without going into the stack"));
	connect(DoesntStackCheck,SIGNAL(stateChanged(int)),this,SLOT(SetDoesntStack()));
	HiddenEffectCheck=new QCheckBox(this);
	HiddenEffectCheck->setObjectName("HiddenEffectCheck");
	HiddenEffectCheck->setText(tr("Effect is not printed on the card"));
	connect(HiddenEffectCheck,SIGNAL(stateChanged(int)),this,SLOT(SetHiddenEffect()));
	QVBoxLayout* ChecksLayout=new QVBoxLayout(CheckBoxesGroup);
	ChecksLayout->addWidget(ManaEffectCheck);
	ChecksLayout->addWidget(DoesntStackCheck);
	ChecksLayout->addWidget(HiddenEffectCheck);

	QVBoxLayout* MainLayout=new QVBoxLayout(this);
	MainLayout->addWidget(EffectPreviewGroup);
	MainLayout->addWidget(NameTextGroup);
	MainLayout->addWidget(EffectTypeGroup);
	MainLayout->addWidget(CostTragetBox);
	MainLayout->addWidget(CheckBoxesGroup);
}
void EffectsBuilder::resizeEvent(QResizeEvent* event){
	Background->setGeometry(0,0,width(),height());
	SymbolsSelector->setGeometry(51*width()/333,18*height()/513,250,130); //FIXME
}
void EffectsBuilder::SetEffectType(int index){
	if (EffectTypeCombo->itemData(index).toInt()==EffectsConstants::EffectTypes::TriggeredEffect){
		TriggersLabel->show();
		AddTriggerCombo->show();
		ResetTriggersButton->show();
	}
	else{
		ResetTriggers();
		TriggersLabel->hide();
		AddTriggerCombo->hide();
		ResetTriggersButton->hide();
	}
	EffectPreview->SetEffectType(EffectTypeCombo->itemData(index).toInt());
	EffectPreview->UpdateAspect();
}
void EffectsBuilder::ResetTriggers(){
	EffectPreview->SetTriggers();
	EffectPreview->UpdateAspect();
}
void EffectsBuilder::AddTrigger(int index){
	if (index==0) return;
	EffectPreview->AddTrigger(AddTriggerCombo->itemData(index).toInt());
	EffectPreview->UpdateAspect();
	AddTriggerCombo->setCurrentIndex(0);
}
void EffectsBuilder::SetManaEffect(){
	EffectPreview->SetManaEffect(ManaEffectCheck->isChecked());
}
void EffectsBuilder::SetHiddenEffect(){
	EffectPreview->SetHiddenEffect(HiddenEffectCheck->isChecked());
	EffectPreview->UpdateAspect();
}
void EffectsBuilder::SetDoesntStack(){
	EffectPreview->SetDoesntStack(DoesntStackCheck->isChecked());
}
void EffectsBuilder::ResetCost(){
	EffectPreview->SetEffectCost();
	EffectPreview->UpdateAspect();
}
void EffectsBuilder::AddCost(int index){
	if (index==0) return;
	EffectPreview->AddEffectCost(AddCostCombo->itemData(index).toInt(),1);
	EffectPreview->UpdateAspect();
	AddCostCombo->setCurrentIndex(0);
}
void EffectsBuilder::SetEffectText(){
	EffectPreview->SetEffectText(EffectTextEditor->toHtml());
	EffectPreview->UpdateAspect();
}
void EffectsBuilder::AddSymbol(int index){
	if (index<0 || index>=Symbols::Num_Symbols) return;
	EffectTextEditor->insertHtml(QString("<img src=\"%1\" height=\"13\" />").arg(Symbols::symbols_paths[index]));
}