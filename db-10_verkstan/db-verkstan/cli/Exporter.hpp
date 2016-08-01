#pragma once

using namespace System;

namespace Verkstan
{
    public ref class Exporter
    {
    public:
        static void ExportAs64K(String^ filename);
        static void ExportAsDemo(String^ filename);
    };
}