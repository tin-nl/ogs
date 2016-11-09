/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 * \file   NonWettingPhaseVanGenuchten.h
 *
 * Created on November 2, 2016, 11:24 AM
 */
#ifndef OGS_NON_WETTING_PHASE_VAN_GENUCHTEN_H
#define OGS_NON_WETTING_PHASE_VAN_GENUCHTEN_H

#include "RelativePermeability.h"

namespace MaterialLib
{
namespace PorousMedium
{
/**
 *   \brief BrookCorey oil-gas model: non-wetting phase
 *
 *   \f[k{rel}= (1 - S_e)^{1/3} (1 - S_e^{1/m})^{2m}\f]
 *   with
 *   \f[S_e=\dfrac{S^w-S_r}{S^w_{\mbox{max}}-S^w_r}\f]
 *   where
 *    \f{eqnarray*}{
 *       &S^w_r&            \mbox{residual saturation of wetting phase,}\\
 *       &S^w_{\mbox{max}}& \mbox{maximum saturation of wetting phase,}\\
 *       &m(<=1) &          \mbox{ exponent.}\\
 *    \f}
 *
 *    Note:
 *     \f[m=1/(1-n)\f].
 */
class NonWettingPhaseVanGenuchten final : public RelativePermeability
{
public:
    /**
     * @param Snr       Residual saturation of the non-wetting phase,
     *                  \f$ S^n_r \f$
     * @param Snmax     Maximum saturation  of the non-wetting phase,
     *                  \f$ S^n_{\mbox{max}} \f$
     * @param m         Exponent, \f$ m \in [0,1]\f$
     * @param krel_min  Minimum relative permeability,
     *                  \f$ k_{rel}^{\mbox{min}}\f$
     */
    NonWettingPhaseVanGenuchten(const double Snr, const double Snmax,
                                const double m, const double krel_min)
        : _Sr(1. - Snmax), _Smax(1. - Snr), _mm(m), _krel_min(krel_min)
    {
    }

    /// Get model name.
    std::string getName() const override
    {
        return "Non-wetting phase van Genuchten relative permeability model.";
    }

    /// Get relative permeability value.
    /// \param saturation_w Non-wetting phase saturation
    double getValue(const double saturation_w) const override;

private:
    const double _Sr;        ///< Residual saturation of wetting phase, 1-Snmax.
    const double _Smax;      ///< Maximum saturation of wetting phase, 1-Snr.
    const double _mm;        ///< Exponent (<=1.0), n=1/(1-mm).
    const double _krel_min;  ///< Minimum relative permeability
};

}  // end namespace
}  // end namespace
#endif /* OGS_NON_WETTING_PHASE_VAN_GENUCHTEN_H */
