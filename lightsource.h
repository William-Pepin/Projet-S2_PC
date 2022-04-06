#pragma once

#include "qge/Vendor.h"
#include "qge/EntityController.h"
#include "qge/Entity.h"

class QTimer;


class LightSource: public qge::EntityController
{
    Q_OBJECT
public:
    LightSource(qge::Entity* entity, double fovAngle=90, double fovDistance=600);
    ~LightSource();

    std::unordered_set<qge::Entity*> entitiesInView();

    void setCheckFrequency(double timesPerSecond);
    double checkFrequency() const;

    void turnOn();
    void turnOff();

    void setShowFOV(bool tf);

public slots:
    void checkFov_();
signals:
    /// Emitted whenever an entity enters the field of view of the entity
    /// controlled.
    void entityEntersFOV(qge::Entity* entity);

    /// Emitted whenever an entity leaves the field of view of the entity
    /// controlled.
    void entityLeavesFOV(qge::Entity* entity);
private:
    double fieldOfViewAngle_;
    double fieldOfViewDistance_;
    double fieldOfViewCheckDelayMs_; // in ms
    QTimer* timerCheckFov_;

    bool showFOV_;
    QGraphicsPolygonItem* fovVisual_;

    // helper
    std::unordered_set<qge::Entity*> entitiesInViewLastTime_;

    // helper functions
    void ensureFOVVisualIsRemoved_();
};

