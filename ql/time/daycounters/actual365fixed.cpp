/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/time/daycounters/actual365fixed.hpp>
#include <boost/make_shared.hpp>

namespace QuantLib {

    boost::shared_ptr<DayCounter::Impl>
    Actual365Fixed::implementation(Actual365Fixed::Convention c) {
        switch (c) {
          case Standard:
            return boost::make_shared<Impl>();
          case Canadian:
            return boost::make_shared<CA_Impl>();
          default:
            QL_FAIL("unknown Actual/365 (Fixed) convention");
        }
    }
    
    Time Actual365Fixed::CA_Impl::yearFraction(const Date& d1, 
                                               const Date& d2, 
                                               const Date& refPeriodStart, 
                                               const Date& refPeriodEnd) const {
        // Need the period to calculate frequency
        QL_REQUIRE(refPeriodStart != Date(),"invalid refPeriodStart");
        QL_REQUIRE(refPeriodEnd != Date(),"invalid refPeriodEnd");

        Time dcs = daysBetween(d1,d2);
        Time dcc = daysBetween(refPeriodStart,refPeriodEnd);
        Integer months = Integer(0.5+12*dcc/365);
        Integer frequency = Integer( 12/months);

        if ( dcs < 365/frequency)
            return dcs/365.0;

        return 1./frequency - (dcc-dcs)/365.0;

    }

}