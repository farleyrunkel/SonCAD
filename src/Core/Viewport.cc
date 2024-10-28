// Copyright [2024] SunCAD

#include "Core/Viewport.h"

// Constructor

Viewport::Viewport(QObject* parent) : Viewport(nullptr, parent) {}

Viewport::Viewport(Workspace* workspace, QObject* parent)
    : QObject(parent), mWorkspace(workspace), mRenderMode(SolidShaded), mTwist(0.0), mScale(100.0) {}

 // Getters and setters for properties

  gp_Pnt Viewport::eyePoint() {
     if (mV3dView) {
         double xEye = 0, yEye = 0, zEye = 0;
         mV3dView->Eye(xEye, yEye, zEye);
         mEyePoint = gp_Pnt(xEye, yEye, zEye);
     }
     return mEyePoint;
 }

   void Viewport::setEyePoint(const gp_Pnt& point) {
      mEyePoint = point;
      if (mV3dView) {
          mV3dView->SetEye(mEyePoint.X(), mEyePoint.Y(), mEyePoint.Z());
          emit eyePointChanged();
      }
  }

   gp_Pnt Viewport::targetPoint() {
      if (mV3dView) {
          double xAt = 0, yAt = 0, zAt = 0;
          mV3dView->At(xAt, yAt, zAt);
          mTargetPoint = gp_Pnt(xAt, yAt, zAt);
      }
      return mTargetPoint;
  }

   void Viewport::setTargetPoint(const gp_Pnt& point) {
      mTargetPoint = point;
      if (mV3dView) {
          mV3dView->SetAt(mTargetPoint.X(), mTargetPoint.Y(), mTargetPoint.Z());
          emit targetPointChanged();
      }
  }

   double Viewport::twist() {
      if (mV3dView) {
          mTwist = mV3dView->Twist() * 180.0 / M_PI;  // Convert to degrees
      }
      return mTwist;
  }

   void Viewport::setTwist(double value) {
      if (mV3dView) {
          mV3dView->SetTwist(value * M_PI / 180.0);  // Convert to radians
          if (mTwist != value) {
              mTwist = value;
              emit twistChanged();
          }
      }
  }

   double Viewport::scale() {
      if (mV3dView) {
          mScale = mV3dView->Scale();
      }
      return mScale;
  }

   void Viewport::setScale(double value) {
      if (mV3dView) {
          mV3dView->SetScale(value);
          if (mScale != value) {
              mScale = value;
              emit scaleChanged();
          }
      }
  }

   Viewport::RenderModes Viewport::renderMode() const {
      return mRenderMode;
  }

   void Viewport::setRenderMode(RenderModes mode) {
      if (mRenderMode != mode) {
          mRenderMode = mode;
          updateRenderMode();
          emit renderModeChanged();
      }
  }

  void Viewport::init(bool useMsaa) {
    if (mV3dView) {
        return;
    }

    mV3dView = mWorkspace->v3dViewer()->CreateView();
    mAisAnimationCamera = new AIS_AnimationCamera("ViewCamera", mV3dView);

    mV3dView->SetBgGradientColors(Quantity_Color(0.624, 0.714, 0.804, Quantity_TOC_sRGB),
        Quantity_Color(0.424, 0.482, 0.545, Quantity_TOC_sRGB),
        Aspect_GFM_VER, false);

    Graphic3d_RenderingParams& renderParams = mV3dView->ChangeRenderingParams();
    renderParams.NbMsaaSamples = useMsaa ? 4 : 0;
    renderParams.IsAntialiasingEnabled = useMsaa;
    renderParams.TransparencyMethod = Graphic3d_RTM_DEPTH_PEELING_OIT;
    renderParams.Method = Graphic3d_RM_RASTERIZATION;
    renderParams.RaytracingDepth = 3;
    renderParams.IsShadowEnabled = true;
    renderParams.IsReflectionEnabled = true;
    renderParams.IsTransparentShadowEnabled = true;

    // Reinitialize view parameters
    setTargetPoint(mTargetPoint);
    setEyePoint(mEyePoint);
    setScale(mScale);
    setTwist(mTwist);
    updateRenderMode();
}

// Function to update render mode

 void Viewport::updateRenderMode() {
    if (!mV3dView) return;

    mV3dView->SetComputedMode(mRenderMode == HLR);

    auto& renderParams = mV3dView->ChangeRenderingParams();
    if (mRenderMode == Raytraced) {
        renderParams.Method = Graphic3d_RM_RAYTRACING;
    }
    else {
        renderParams.Method = Graphic3d_RM_RASTERIZATION;
    }
}

// Destructor

 Viewport::~Viewport() {
    delete mAisAnimationCamera;
    if (mV3dView) {
        mV3dView->Remove();
    }
}
