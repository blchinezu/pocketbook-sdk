 #ifndef PAY_ONLINE_H_
#define PAY_ONLINE_H_

#include <string>
#include <vector>

namespace pocketbook
{
namespace pay_online
{

struct  __attribute__ ((visibility ("default"))) Card {
    std::string id;
    std::string label;
    Card(const std::string& id_p, const std::string& label_p):id(id_p),label(label_p){}
    Card(){}
};

struct  __attribute__ ((visibility ("default"))) CurrenciesParam
{
    std::string payment_currency;
    std::string transaction_currency;
    double rate;
};

struct  __attribute__ ((visibility ("default"))) Order
{
    std::string order_id;
    std::string api_url;
};

class __attribute__ ((visibility ("default"))) ServerApi
{
public:
    class  __attribute__ ((visibility ("default"))) ICallback{
    public:
        virtual void GetCardListResult(int /*rc*/, const std::vector<Card>& /*cards*/){}
        virtual void GetCurrenciesResult(int /*rc*/, const CurrenciesParam& /*param*/){}
        virtual void GetPaymentUrlResult(int /*rc*/, const Order& /*order*/){}
        virtual void GetRebillUrlResult(int /*rc*/, const Order& /*order*/){}
        virtual void DeleteCardResult(int /*rc*/, bool /*is_succeed*/){}

        enum TransactionStatus {
            kOk,
            kPending,
            kNotPaid,
        };

        virtual void GetPaymentStatusResult(int /*rc*/, TransactionStatus /*status*/){}
    };

    virtual int GetCardListAsync(ICallback* callback) = 0;
    virtual int GetCurrenciesAsync(ICallback* callback) = 0;
    virtual int GetPaymentUrlAsync(double amount, const std::string& currency, bool rebill_remember, ICallback* callback) = 0;
    virtual int GetRebillUrlAsync(double amount, const std::string& currency, const std::string card_id, ICallback* callback) = 0;
    virtual int GetPaymentStatusAsync(const std::string& order_id, ICallback* callback) = 0;
    virtual int DeleteCardAsync(const std::string& card_id, ICallback* callback) = 0;

    enum Result {
        kOk,
        kCancelled,
        kFailed,
    };

    virtual int SetResult(Result result, double amount) = 0;
    virtual int ProcessNewData(void) = 0;

    virtual ~ServerApi();
};

class __attribute__ ((visibility ("default"))) PayOnline
{
public:
    PayOnline();
    int Init(ServerApi* callback);

    int StartPayment(double recommended_amount);
private:

    ServerApi* callback_;
};

}
}
#endif // PAY_ONLINE_H_
