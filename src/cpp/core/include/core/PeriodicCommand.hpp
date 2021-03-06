/*
 * PeriodicCommand.hpp
 *
 * Copyright (C) 2009-12 by RStudio, Inc.
 *
 * This program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */


#ifndef CORE_PERIODIC_COMMAND_HPP
#define CORE_PERIODIC_COMMAND_HPP

#include <core/ScheduledCommand.hpp>

namespace core {

class PeriodicCommand : public ScheduledCommand
{
public:
   PeriodicCommand(const boost::posix_time::time_duration& period,
                   const boost::function<bool()>& execute)
      : ScheduledCommand(execute),
        period_(period),
        nextExecutionTime_(now())
   {
   }

   virtual ~PeriodicCommand() {}

   // COPYING: boost::noncopyable

public:
   virtual void execute()
   {
      if (now() > nextExecutionTime_)
      {
         if (execute_())
         {
            nextExecutionTime_ = now() + period_;
         }
         else
         {
            finished_ = true;
         }
      }
   }

private:
   const boost::posix_time::time_duration period_;
   boost::posix_time::ptime nextExecutionTime_;
};



} // namespace core


#endif // CORE_PERIODIC_COMMAND_HPP
