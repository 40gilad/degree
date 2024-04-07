using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Models
{
    public class RoomTime
    {
        private float _maxTurnTime; //10 seconds
        private DateTime _startDate;

        public RoomTime(float maxTurnTime)
        {
            _maxTurnTime = maxTurnTime;
        }

        public void ResetTimer()
        {
            _startDate = DateTime.UtcNow;
        }

        public bool IsCurrentTimeActive()
        {
            if (_startDate != null)
            {
                TimeSpan diff = DateTime.UtcNow - _startDate;
                if (diff.TotalSeconds < _maxTurnTime)
                    return true;
            }
            return false;
        }
    }
}
