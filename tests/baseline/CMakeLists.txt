# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Special case: test includes the QBaselineTest module sources from qtbase directly
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../qtbase/tests/baseline/shared" AND QT_FEATURE_process)
    add_subdirectory(scenegrabber)
    add_subdirectory(lottie)
endif()
