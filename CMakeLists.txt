cmake_minimum_required(VERSION 4.0)
project(Coffee_Processing_Factory_Simulation)

set(CMAKE_CXX_STANDARD 26)

add_executable(Coffee_Processing_Factory_Simulation main.cpp
        include/Core/Entity.h
        include/Core/Worker.h
        src/Core/Worker.cpp
        include/Core/CoreTypes.h
        include/Core/Batch.h
        include/Core/Machine.h
        include/Harvest/FarmPlot.h
        src/Core/Batch.cpp
        src/Core/Machine.cpp
        src/Harvest/FarmPlot.cpp
        include/Harvest/Harvester.h
        src/Harvest/Harvester.cpp
        include/Reception/ReceptionScale.h
        src/Reception/ReceptionScale.cpp
        include/Reception/ReceptionClerk.h
        include/Reception/IntakeRecord.h
        src/Reception/ReceptionClerk.cpp
        include/Quality/QualityInspector.h
        include/Quality/GradeResult.h
        src/Quality/QualityInspector.cpp
        include/Core/Utils.h
        src/Core/Utils.cpp
        include/Cleaning/FlotationTank.h
        src/Cleaning/FlotationTank.cpp
        include/Cleaning/DebrisRemover.h
)
