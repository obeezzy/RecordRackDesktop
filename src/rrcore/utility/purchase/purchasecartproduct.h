#ifndef PURCHASECARTPRODUCT_H
#define PURCHASECARTPRODUCT_H

#include "utility/user/user.h"
#include "utility/commonutils.h"
#include "utility/stockutils.h"
#include <QVariantList>
#include <QList>
#include <QVariantList>
#include <QVariantMap>
#include <QDateTime>

namespace Utility {
struct PurchaseCartProduct {
    int id {-1};
    QString product;
    StockProductCategory category;
    QString description;
    QUrl imageUrl;
    qreal quantity;
    qreal availableQuantity;
    StockProductUnit unit;
    qreal costPrice {0.0};
    qreal retailPrice {0.0};
    qreal unitPrice {0.0};
    qreal cost {0.0};
    qreal amountPaid {0.0};
    QString currency;
    Note note;
    RecordGroup::Flags flags;
    QDateTime created;
    QDateTime lastEdited;
    User user;

    explicit PurchaseCartProduct() = default;
    explicit PurchaseCartProduct(int id);
    explicit PurchaseCartProduct(const QVariantMap &product);
    explicit PurchaseCartProduct(const StockProductCategory &category,
                                 const QString &product,
                                 const QString &description,
                                 const QUrl &imageUrl,
                                 qreal quantity,
                                 const StockProductUnit &unit,
                                 const RecordGroup::Flags &flags,
                                 qreal costPrice,
                                 qreal retailPrice,
                                 const QString &currency,
                                 const Note &note);
    explicit PurchaseCartProduct(int id,
                                 const QString &product,
                                 const StockProductCategory &category,
                                 qreal quantity,
                                 const StockProductUnit &unit,
                                 qreal retailPrice,
                                 qreal unitPrice,
                                 qreal cost,
                                 qreal amountPaid,
                                 const Note &note);
    QVariantMap toVariantMap() const;

    inline bool operator==(const PurchaseCartProduct &other) {
        return id == other.id;
    }
};

class PurchaseCartProductList : public QList<PurchaseCartProduct> {
public:
    explicit PurchaseCartProductList() {}
    explicit PurchaseCartProductList(std::initializer_list<PurchaseCartProduct> productList) :
        QList<PurchaseCartProduct>(productList) {}
    explicit PurchaseCartProductList(const QVariantList &list) :
        QList<PurchaseCartProduct>() {
        for (const auto &variant : list)
            append(PurchaseCartProduct{variant.toMap()});
    }

    inline QVariantList toVariantList() const {
        QVariantList list;
        for (const auto &stockProduct : *this)
            list.append(stockProduct.toVariantMap());
        return list;
    }
};
}
Q_DECLARE_TYPEINFO(Utility::PurchaseCartProduct, Q_PRIMITIVE_TYPE);

#endif // PURCHASECARTPRODUCT_H