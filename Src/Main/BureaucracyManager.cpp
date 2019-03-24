#include "BureaucracyManager.h"

std::unique_ptr<BureauCrazyManager> BureauCrazyManager::instance_;


BureauCrazyManager::BureauCrazyManager(std::string jsonInit) 
	: ruptcyStartTime_(0), startedToCount_(false), bankruptcy_(false),
	actualMoney_(0),visitors_(0)
{
	json jfile = GestorRecursos::instance()->getJsonByKey(jsonInit);

	for (json taxes : jfile["Taxes"]) 
	{
		TaxBill bill = { TaxType(taxes["Id"]), taxes["Amount"] };
		bills_.push_back(bill);
	}

	ruptcyMaxTime_ = jfile["BankRuptcy"]["ruptcyMaxTime"];
	floorRuptcyMoney_ = jfile["BankRuptcy"]["floorRuptcyMoney"];
	Time2Tax_ = jfile["BankRuptcy"]["InitialTime2Tax"];

}

void BureauCrazyManager::checkBankRuptcy()
{
	if (!startedToCount_ && actualMoney_ < floorRuptcyMoney_) {
		ruptcyStartTime_ = time(0); //Empieza a contar
		startedToCount_ = true;
	}
	if (startedToCount_ && ((time(0) - ruptcyStartTime_) >= ruptcyMaxTime_)) //Ha superado el tiempo maximo que se puede estar en negativo
	{
		bankruptcy_ = true;

	}
	if (actualMoney_ > floorRuptcyMoney_) { //Si vuelvo a estar en positivo dejo de contar
		startedToCount_ = false;
	}	
}

void BureauCrazyManager::taxCollect(TaxType taxType)
{
	actualMoney_ -= bills_[taxType].amount_;
}

void BureauCrazyManager::taxCollectALL()
{
	for (TaxBill t : bills_) {
		actualMoney_ -= t.amount_;
	}
}

void BureauCrazyManager::addAmountToTax(TaxType type, float amount)
{
	bills_[type].amount_ += amount;
}

void BureauCrazyManager::changeTaxAmount(TaxType type, float amount)
{
	bills_[type].amount_ = amount;
}

BureauCrazyManager::~BureauCrazyManager()
{
	instance_.release();
}

bool BureauCrazyManager::bankruptcy()
{
	return bankruptcy_;
}

BureauCrazyManager * BureauCrazyManager::instance(std::string jsonInit)
{
	if (instance_.get() == nullptr) {
		instance_.reset(new BureauCrazyManager(jsonInit));
	}
	else return instance_.get();
}


