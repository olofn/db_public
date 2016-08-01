using System;
using System.Collections.Generic;
using System.Text;

namespace DB.DoF
{
    public struct SmoothFloat
    {
        float value;
        public float Value { get { return value; } }

        public float Target;

        public float Diff { get { return Target - value; } }

        float speed;

        public SmoothFloat(float value, float speed)
        {
            this.value = Target = value;
            this.speed = speed;
        }

        public void Update()
        {
            this.value += Diff*speed;
        }
    }
}
