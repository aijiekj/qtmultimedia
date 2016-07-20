/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Copyright (C) 2016 Ruslan Baratov
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qandroidviewfindersettingscontrol.h"
#include "qandroidcamerasession.h"

QT_BEGIN_NAMESPACE

QAndroidViewfinderSettingsControl2::QAndroidViewfinderSettingsControl2(QAndroidCameraSession *session)
    : m_cameraSession(session)
{
}

QList<QCameraViewfinderSettings> QAndroidViewfinderSettingsControl2::supportedViewfinderSettings() const
{
    QList<QCameraViewfinderSettings> viewfinderSettings;

    const QList<QSize> previewSizes = m_cameraSession->getSupportedPreviewSizes();
    const QList<QVideoFrame::PixelFormat> pixelFormats = m_cameraSession->getSupportedPixelFormats();
    const QList<AndroidCamera::FpsRange> fpsRanges = m_cameraSession->getSupportedPreviewFpsRange();

    viewfinderSettings.reserve(previewSizes.size() * pixelFormats.size() * fpsRanges.size());

    for (const QSize& size : previewSizes) {
        for (QVideoFrame::PixelFormat pixelFormat : pixelFormats) {
            for (const AndroidCamera::FpsRange& fpsRange : fpsRanges) {
                QCameraViewfinderSettings s;
                s.setResolution(size);
                s.setPixelAspectRatio(QSize(1, 1));
                s.setPixelFormat(pixelFormat);
                s.setMinimumFrameRate(fpsRange.getMinReal());
                s.setMaximumFrameRate(fpsRange.getMaxReal());
                viewfinderSettings << s;
            }
        }
    }
    return viewfinderSettings;
}

QCameraViewfinderSettings QAndroidViewfinderSettingsControl2::viewfinderSettings() const
{
    return m_cameraSession->viewfinderSettings();
}

void QAndroidViewfinderSettingsControl2::setViewfinderSettings(const QCameraViewfinderSettings &settings)
{
    m_cameraSession->setViewfinderSettings(settings);
}

QT_END_NAMESPACE

#include "moc_qandroidviewfindersettingscontrol.cpp"