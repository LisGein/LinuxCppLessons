import math
import gen_tex

def calc_betta(specific_gas_const, k, Tk):
    A = math.sqrt(2 / (k + 1)) * (2 / (k + 1)) ** (1 / (k - 1))
    betta = math.sqrt(specific_gas_const * Tk) / A
    return betta

def calc_gdf_Tau(lambda_, k):
    return (1 - (k - 1) / (k + 1) * lambda_ ** 2)

def calc_gdf_pi(lambda_, k):
    gdf_pi = (1 - (k - 1) / (k + 1) * lambda_ ** 2) ** (k / (k - 1))
    return gdf_pi

def calc_gdf_esp(lambda_, k):
    gdf_eps = (1 - (k - 1) / (k + 1) * lambda_ ** 2) ** (1 / (k - 1))
    return gdf_eps

def calc_gdf_qu(lambda_, k):
    gdf_qu = ((k + 1) / 2) ** (1 / (k - 1)) * lambda_ * calc_gdf_esp(lambda_, k)
    return gdf_qu

def calc_Fkr(rho, Sg0, u1, betta, P0, Pk, nu):
    u = u1 * (Pk / P0) ** nu
    Fkr = (rho * Sg0 * u * betta) / Pk
    return Fkr

def calc_cilindr(D2, D_max, L):
    if D2 >= D_max or L < 0:
        cilindr = 0.000001
    else:
        cilindr = 3.1415926 * D2 * L
    return cilindr

def calc_kolco(D_out, D_in, D_max):
    return math.pi / 4 * (min(D_out, D_max) ** 2 - min(D_in, D_max) ** 2)

def calc_bari(rho, Sg, u1, betta, Fkr, P0, nu):
    Pk = ((rho * Sg * u1 * betta) / (Fkr * P0 ** nu)) ** (1 / (1 - nu))
    return Pk

def calc_lambda(Fkr_Fi, k, x):
    diff_o = (x * ((k + 1) / 2) ** (1 / (k - 1)) * (1 - (k - 1) / (k + 1) * x ** 2) ** (1 / (k - 1)) - Fkr_Fi) * (
    k * (x ** 2 - 1) - x ** 2 - 1)
    diff_s = (k + 1) ** (k / (k - 1)) * (x ** 2 - 1) * ((-k * x ** 2 + k + x ** 2 + 1) / (2 * k + 2)) ** (1 / (k - 1))
    x_1 = x - (diff_o / diff_s)
    return x_1

def calc_burn_change_x(idx, L10, L20, D20, D30):
    x = [0, L10[idx], ]
    if D30[idx] > 0.25:
        x.append(L10[idx])
        x.append(L20[idx])
    else:
        x.append(L10[idx])
        x.append(L20[idx])
    if D20[idx] > 0.25:
        x.append(L20[idx])
        x.append(0)
    else:
        x.append(L20[idx])
        x.append(0)
    x.append(0)
    x.append(0)
    x.append(L10[idx])
    if D30[idx] > 0.25:
        x.append(L10[idx])
        x.append(L20[idx])
    else:
        x.append(L10[idx])
        x.append(L20[idx])
    if D20[idx] > 0.25:
        x.append(L20[idx])
        x.append(0)
    else:
        x.append(L20[idx])
        x.append(0)
    x.append(0)
    return x

def calc_burn_change_y(idx, D10_, D20, D30):
    y = [D10_ / 2, D10_ / 2, ]
    if D30[idx] > 0.25:
        y.append(0.25)
        y.append(0.25)
    else:
        y.append(0.25)
        y.append(D30[idx])
    if D20[idx]/2 > 0.25:
        y.append(0.25)
        y.append(0.25)
    else:
        y.append(D20[idx] / 2)
        y.append(D20[idx] / 2)
    y.append(D10_ / 2)
    y.append(-D10_ / 2)
    y.append(-D10_ / 2)
    if D30[idx]/2 > 0.25:
        y.append(-0.25)
        y.append(-0.25)
    else:
        y.append(-D30[idx] / 2)
        y.append(-D30[idx] / 2)
    if D20[idx]/2 > 0.25:
        y.append(-0.25)
        y.append(-0.25)
    else:
        y.append(-D20[idx] / 2)
        y.append(-D20[idx] / 2)
    y.append(-D10_ / 2)
    return y

class CalcCourseWork:
    def __init__(self):
        self.speed_burn = 2
        self.idx_speed_burn = 0.001
        self.burning_rate = 0.2
        self.idx_burning_rate = 1
        self.base_pressure = 100000
        self.idx_base_pressure = 1
        self.ind_isentrope = 1.2
        self.idx_ind_isentrope = 1
        self.estimated_pressure_cc = 14
        self.idx_estimated_pressure_cc = 1000000
        self.estimated_pressure_ne = 20
        self.idx_estimated_pressure_ne = 1000
        self.temp_cc = 3100
        self.idx_temp_cc = 1
        self.molar_mass_ps = 35
        self.idx_molar_mass_ps = 1
        self.fuel_density = 1600
        self.idx_fuel_density = 1
        self.time_step = 0.12
        self.idx_time_step = 1
        self.lambda_ = 2.70341305125348
        self.l1 = 1.5  # length parameter
        self.idx_l1 = 1
        self.l2 = 1  # length parameter
        self.idx_l2 = 1
        self.d1 = 0.5  # diam parameter
        self.idx_d1 = 1
        self.d2 = 0.25  # diam parameter
        self.idx_d2 = 1
        self.d3 = 0.3  # diam parameter
        self.idx_d3 = 1
        self.PI = 3.1415
        self.Fa = 0.0734624980076733
        self.t_calc = []
        self.agle1 = 50
        self.agle2 = 20

    def calc_data(self):
        self.u = self.speed_burn * self.idx_speed_burn
        self.nu = self.burning_rate * self.idx_burning_rate
        self.P0 = self.base_pressure * self.idx_base_pressure
        self.k = self.ind_isentrope * self.idx_ind_isentrope
        self.P_k = self.estimated_pressure_cc * self.idx_estimated_pressure_cc
        self.Pa = self.estimated_pressure_ne * self.idx_estimated_pressure_ne
        self.Tk = self.temp_cc * self.idx_temp_cc
        self.mu = self.molar_mass_ps * self.idx_molar_mass_ps
        self.specific_gas_const = (8314.0 / self.mu)
        self.rho = self.fuel_density * self.idx_fuel_density
        self.h = self.time_step * self.idx_time_step
        self.betta = calc_betta(self.specific_gas_const, self.k, self.Tk)
        self.Akr = math.sqrt(2 * self.k / (self.k + 1) * self.specific_gas_const * self.Tk)
        self.gdf_pi = calc_gdf_pi(self.lambda_, self.k)
        self.gdf_eps = calc_gdf_esp(self.lambda_, self.k)
        self.gdf_qu = calc_gdf_qu(self.lambda_, self.k)
        self.va = self.Akr * self.lambda_
        self.L10_ = self.l1 * self.idx_l1
        self.L20_ = self.l2 * self.idx_l2
        self.D10_ = self.d1 * self.idx_d1
        self.D20_ = self.d2 * self.idx_d2
        self.D30_ = self.d3 * self.idx_d3
        self.L30 = self.L10_ - self.L20_
        self.s10 = calc_cilindr(self.D20_, self.D10_, self.L20_)
        self.s20 = calc_kolco(self.D10_, self.D20_, self.D10_)
        self.s30 = calc_cilindr(self.D30_, self.D10_, self.L30)
        self.s40 = calc_kolco(self.D10_, self.D30_, self.D10_)
        self.Sg0 = self.s10 + self.s20 + self.s30 + self.s40
        self.Fkr = calc_Fkr(self.rho, self.Sg0, self.u, self.betta, self.P0, self.P_k, self.nu)
        self.Dkr = math.sqrt(self.Fkr * 4 / self.PI)
        self.Da = math.sqrt(self.Fa * 4 / self.PI)
        x_t = 0
        x_li = 0

        self.li = []
        self.D20 = []
        self.D30 = []
        self.L10 = []
        self.L20 = []
        self.L30 = []
        self.S10_ = []
        self.S20_ = []
        self.S30_ = []
        self.S40_ = []
        self.Sg = []
        self.pk = []
        self.Gc = []
        self.pa = []
        self.u_Pk = []
        self.P = []
        self.I_spec = []

        for i in range(201):
            self.t_calc.append(x_t)
            x_t = x_t + self.h
            self.li.append(x_li)
            x_d20 = self.D20_ + 2 * self.li[i]
            if x_d20 > 0.5:
                self.D20.append(0.5)
            else:
                self.D20.append(x_d20)
            x_d30 = self.D30_ + 2 * self.li[i]
            if x_d30 > 0.5:
                self.D30.append(0.5)
            else:
                self.D30.append(x_d30)
            x_l10 = self.L10_ - self.li[i]
            self.L10.append(x_l10)
            x_l20 = self.L20_ - self.li[i]
            self.L20.append(x_l20)
            self.L30.append(self.L10[i] - self.L20[i])
            x_s10 = calc_cilindr(self.D20[i], self.D10_, self.L20[i])
            self.S10_.append(x_s10)
            x_s20 = calc_kolco(self.D10_, self.D20[i], self.D10_)
            self.S20_.append(x_s20)
            x_s30 = calc_cilindr(self.D30[i], self.D10_, self.L30[i])
            self.S30_.append(x_s30)
            x_s40 = calc_kolco(self.D10_, self.D30[i], self.D10_)
            self.S40_.append(x_s40)
            self.Sg.append(self.S10_[i] + self.S20_[i] + self.S30_[i] + self.S40_[i])
            x_pk = calc_bari(self.rho, self.Sg[i], self.u, self.betta, self.Fkr, self.P0, self.nu)
            self.pk.append(x_pk)
            x_Gc = self.pk[i] * self.Fkr / self.betta
            self.Gc.append(x_Gc)
            x_pa = self.pk[i] * self.gdf_pi
            self.pa.append(x_pa)
            x_uPk = self.u * (self.pk[i] / self.P0) ** self.nu
            self.u_Pk.append(x_uPk)
            x_li = x_li + self.u_Pk[i] * self.h
            x_p = self.va * self.Gc[i] + self.Fa * (self.pa[i] - self.Pa)
            self.P.append(x_p)
            if self.Gc[i] > 0.001:
                x_I_spes = self.P[i] / self.Gc[i]
            else:
                x_I_spes = 0
            self.I_spec.append(x_I_spes)
        self.t_calc.append(x_t)
        self.q = []
        self.q.append(1)
        self.q.append(2.45)
        self.phi1 = math.radians(self.agle1)
        self.phi2 = math.radians(self.agle2)
        self.Fkr_Fa = self.Fkr / self.Fa
        self.lambda_max = math.sqrt((self.k + 1) / (self.k - 1))
        self.diff1 = self.gdf_pi - self.Pa / self.P_k
        self.diff2 = self.gdf_qu - self.Fkr_Fa
        self.L_bpn = (self.D10_ - self.Dkr) / (2 * math.tan(self.phi1))
        self.L_apn = (self.Da - self.Dkr) / (2 * math.tan(self.phi2))
        self.Fkr_Fa = self.Fkr / self.Fa
        X_bpn = self.L_bpn / 5
        X_apn = self.L_apn / 15
        self.I = []
        self.L_i = []
        self.D_i = []
        self.F_i = []
        self.Fkr_Fi = []
        self.lambda_i = []
        self.lambda_i.append(0.0034)  # lambda???
        self.gdf_qu_l = []
        self.gdf_pi_l = []
        self.gdf_tau_l = []
        self.gdf_eps_l = []
        self.diff_q_Fkr = []
        self.P_ = []  # wervjwjervkwcevkwclkwscowkeocwoeckwkeock viwe ewe
        self.T = []
        self.R_0 = []
        self.v = []

        for i in range(21):
            self.diff_q_Fkr.append(0)
            self.I.append(-5 + i)
            if self.I[i] < 0:
                self.L_i.append(X_bpn * self.I[i])
                x_Di = self.Dkr + ((self.D10_ - self.Dkr) / 5) * (-self.I[i])
            else:
                self.L_i.append(X_apn * self.I[i])
                x_Di = self.Dkr + ((self.Da - self.Dkr) / 15) * (self.I[i])
            self.D_i.append(x_Di)
            x_Fi = self.PI * (self.D_i[i] ** 2 / 4)
            self.F_i.append(x_Fi)
            self.Fkr_Fi.append(self.Fkr / self.F_i[i])
            x_lambda = calc_lambda(self.Fkr_Fi[i], self.k, self.lambda_i[i])
            self.lambda_i.append(x_lambda)
            x_gdf = calc_gdf_qu(self.lambda_i[i + 1], self.k)
            self.gdf_qu_l.append(x_gdf)
            x_gdf = calc_gdf_pi(self.lambda_i[i + 1], self.k)
            self.gdf_pi_l.append(x_gdf)
            x_gdf = calc_gdf_Tau(self.lambda_i[i + 1], self.k)
            self.gdf_tau_l.append(x_gdf)
            x_gdf = calc_gdf_esp(self.lambda_i[i + 1], self.k)
            self.gdf_eps_l.append(x_gdf)
            x = self.gdf_pi_l[i] * long(self.P_k)
            self.P_.append(long(x))
            x = self.Tk * self.gdf_tau_l[i]
            self.T.append(x)
            x = self.P_k / (self.specific_gas_const * self.Tk) * self.gdf_eps_l[i]
            self.R_0.append(x)
            x = self.Akr * self.lambda_i[i + 1]
            self.v.append(x)

    def calc_profile_nozzle(self):
        self.x_prof = []
        self.x_prof.append(0)
        self.x_prof.append(self.x_prof[0])
        self.x_prof.append(-self.L_bpn)
        self.x_prof.append(-self.L_bpn)
        self.x_prof.append(0)
        self.x_prof.append(self.L_apn)
        self.x_prof.append(self.L_apn)
        self.x_prof.append(0)
        self.x_prof.append(-self.L_bpn)
        self.x_prof.append(-self.L_bpn)
        self.x_prof.append(self.x_prof[0])

        self.y_prof = []
        self.y_prof.append(self.D10_/2)
        self.y_prof.append(-self.D10_/2)
        self.y_prof.append(-self.D10_/2)
        self.y_prof.append(self.D10_/2)
        self.y_prof.append(self.Dkr/2)
        self.y_prof.append(self.Da/2)
        self.y_prof.append(-self.Da/2)
        self.y_prof.append(-self.Dkr/2)
        self.y_prof.append(-self.D10_/2)
        self.y_prof.append(self.D10_/2)
        self.y_prof.append(self.D10_/2)

    def print_initial_data(self):
        gen_tex.initial_data_begin_table()
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ('Length', self.l1, 'm', self.idx_l1, 'L10', self.L10_, 'm')
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (' ', self.l2, 'm', self.idx_l2, 'L20', self.L20_, 'm')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ('Diam', self.d1, 'm', self.idx_d1, 'D10', self.D10_, 'm')
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (' ', self.d2, 'm', self.idx_d2, 'D20', self.D20_, 'm')
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (' ', self.d3, 'm', self.idx_d3, 'D30', self.D30_, 'm')
        print("\\hline")
        print("\\multicolumn{6}{|c}{Data on fuel and combustion products} & \\\\")
        print("\\hline")
        print '%s & %d & %s & %d & %s & %f & %s \\\\' % (
        'The burning rate', self.speed_burn, 'mm/s', self.idx_speed_burn, 'u', self.u, 'm/s')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (
        'The index rate', self.burning_rate, ' - ', self.idx_burning_rate, '$\\nu$', self.nu, ' - ')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
        'The base pressure for the unit speed', self.base_pressure, 'Pascal', self.idx_base_pressure, '$P_0$', self.P0,
        'Pascal')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (
        'Indicator isentrope combustion', self.ind_isentrope, ' - ', self.idx_ind_isentrope, 'k', self.k, ' - ')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
            'Calculated value of the pressure in the CC', self.estimated_pressure_cc, 'MPascal',
            self.idx_estimated_pressure_cc, '$P_k$', self.P_k, 'Pascal')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
            'Estimated value of the pressure at the nozzle exit', self.estimated_pressure_ne, 'kPascal',
            self.idx_estimated_pressure_ne, '$P_a$', self.Pa, 'Pascal')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
            'The temperature in the combustion chamber', self.temp_cc, 'K', self.idx_temp_cc, '$T_k$', self.Tk, 'K')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
            'Molar Mass', self.molar_mass_ps, 'mole', self.idx_molar_mass_ps, '$\\mu$', self.mu, 'mole')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
            'The specific gas constant', '', '', '', '$R_{spec}$', self.specific_gas_const, 'J/(kg*K)')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
            'Fuel Density', self.fuel_density, 'kg/$m^3$', self.idx_fuel_density, '$\\rho$', self.rho, 'kg/$m^3$')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (
        'The time step', self.time_step, ' - ', self.idx_time_step, 'h', self.h, ' ')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Consumables complex', '', '', '', '$\\beta$', self.betta, ' ')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
        'Critical speed of sound', '', '', '', '$A_{kr}$', self.Akr, ' ')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Throat area', '', '', '', '$F_{kr}$', self.Fkr, '$m^2$')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
            'The diameter of the critical cross-section', '', '', '', '$D_{kr}$', self.Dkr, ' ')
        print("\\hline")
        print("\\multicolumn{6}{|c}{The geometry of the subsonic part of the nozzle: conical} & \\\\")
        print("\\hline")
        print '%s & %d & %s & %s & %s & %f & %s \\\\' % (
        'Angle', self.agle1, 'grade', '', '$\\phi_1$', self.phi1, 'radians')
        print("\\hline")
        print("\\multicolumn{6}{|c}{The geometry of the supersonic part of the nozzle: conical} & \\\\")
        print("\\hline")
        print '%s & %d & %s & %s & %s & %f & %s \\\\' % (
        'Angle', self.agle2, 'grade', '', '$\\phi_2$', self.phi2, 'radians')
        gen_tex.end_table()

    def print_calculated_data(self):
        gen_tex.calc_data_begin_table()
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
        'The diameter at the nozzle exit', '', '', '', '$D_a$', self.Da, 'm')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
        'Cross-sectional area at the nozzle exit', '', '', '', '$F_a$', self.Fa, '$m^2$')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Area ratio', '', '', '', 'Fkr/Fa', self.Fkr_Fa, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('Maximum dimensionless speed', '', '', '', '$\\lambda_{max}$', self.lambda_max, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('The dimensionless speed', '', '', '', '$\\lambda$', self.lambda_, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('Speed at the nozzle exit', '', '', '', '$\\nu_a$', self.va, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('Gas-dynamic functions', '', '', '', '$\\pi(\\lambda$)', self.gdf_pi, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('Gas-dynamic functions', '', '', '', '$\\varepsilon(\\lambda$)', self.gdf_eps, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('Gas-dynamic functions', '', '', '', 'q($\\lambda$)', self.gdf_qu, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('The difference to the PI(lambda * a) - Pa / Pk', '', '', '', '', self.diff1, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('The difference to the qu(lambda * a) - Fkr / Fa', '', '', '', '', self.diff2, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
              ('The length of the subsonic part of the nozzle', '', '', '', '$L_{bpn}$', self.L_bpn, 'm')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s  \\\\' % \
              ('The length of the supersonic part of the nozzle', '', '', '', '$L_{apn}$', self.L_apn, 'm')
        gen_tex.end_table()
        print("\\end{center}")

    def print_dimensioning(self):
        gen_tex.dimensioning_begin_table()
        for i in range(63):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (
            self.t_calc[i], self.li[i], self.D20[i], self.D30[i], self.L10[i], self.L20[i], self.L30[i], self.S10_[i],
            self.S20_[i], self.S30_[i], self.S40_[i], self.Sg[i], self.pk[i], self.Gc[i], self.pa[i], self.I_spec[i],
            self.P[i], self.u_Pk[i])
        gen_tex.dimensioning_table()
        for i in range(67):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (
            self.t_calc[i + 63], self.li[i + 63], self.D20[i + 63], self.D30[i + 63], self.L10[i + 63], self.L20[i + 63],
            self.L30[i + 63], self.S10_[i + 63], self.S20_[i + 63], self.S30_[i + 63], self.S40_[i + 63],
            self.Sg[i + 63], self.pk[i + 63], self.Gc[i + 63], self.pa[i + 63], self.I_spec[i + 63], self.P[i + 63],
            self.u_Pk[i + 63])
        gen_tex.dimensioning_table()
        for i in range(66):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (
            self.t_calc[i + 130], self.li[i + 130], self.D20[i + 130], self.D30[i + 130], self.L10[i + 130],
            self.L20[i + 130], self.L30[i + 130], self.S10_[i + 130], self.S20_[i + 130], self.S30_[i + 130],
            self.S40_[i + 130], self.Sg[i + 130], self.pk[i + 130], self.Gc[i + 130], self.pa[i + 130],
            self.I_spec[i + 130], self.P[i + 130], self.u_Pk[i + 130])
        gen_tex.dimensioning_table()
        for i in range(5):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (
            self.t_calc[i + 196], self.li[i + 196], self.D20[i + 196], self.D30[i + 196], self.L10[i + 196],
            self.L20[i + 196], self.L30[i + 196], self.S10_[i + 196], self.S20_[i + 196], self.S30_[i + 196],
            self.S40_[i + 196], self.Sg[i + 196], self.pk[i + 196], self.Gc[i + 196], self.pa[i + 196],
            self.I_spec[i + 196], self.P[i + 196], self.u_Pk[i + 196])
        gen_tex.end_table()

    def print_graphics(self):
        print("\\begin{center}")
        print("\\begin{large}")
        print("\\textbf{\\textit {Graphs}}\\\\")
        print("\\end{large}")
        print("\\end{center}")

        gen_tex.begin_graphic(" $D_2$, $D_3$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.D20[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.D30[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 2$: Changing the diameter of the charge during engine operation')
        gen_tex.begin_graphic("$L_1$, $L_2$, $L_3$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.L10[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = yellow] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.L20[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.L30[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 3$: Changing the length of the charge during engine operation')
        gen_tex.begin_graphic("$G_c$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.Gc[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 4$: Changes in consumption during engine operation')
        gen_tex.begin_graphic("$S_1$, $S_2$, $S_3$, $S_4$, $S_g$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.S10_[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.S20_[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = yellow] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.S30_[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = purple] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.S40_[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = green] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.Sg[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 5$: Changing the burning area of the charge during engine operation')
        gen_tex.begin_graphic("$p_k$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.pk[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 6$: The change in pressure in the combustion chamber while the engine')
        gen_tex.begin_graphic("$u(P_k)$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.u_Pk[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 7$: Changing the speed of the combustion of fuel during engine operation')
        gen_tex.begin_graphic("P")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.P[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 8$: Change thrust during engine operation')
        gen_tex.begin_graphic("$I_{spec}$")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(200):
            print '( %f , %f )' % (self.t_calc[i], self.I_spec[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 9$: Changing specific impulse while the engine')

    def print_constr_model_combustion(self):
        print("\\begin{center}")
        print("\\begin{large}")
        print("\\textbf{\\textit {Burning charge}}\\\\")
        print("\\end{large}")

        self.x_f_t = (0, self.L10_, self.L10_, self.L20_, self.L20_,
                      0, 0, 0, self.L10_, self.L10_, self.L20_,
                      self.L20_, 0, 0)
        self.y_f_t = (self.D10_ / 2, self.D10_ / 2,  self.D30_ / 2, self.D30_ / 2,  self.D20_ / 2,
                      self.D20_ / 2, self.D10_ / 2, -self.D10_ / 2, -self.D10_ / 2,  -self.D30_ / 2,  -self.D30_ / 2,
                      -self.D20_ / 2, -self.D20_ / 2,-self.D10_ / 2)
        gen_tex.begin_tableN4(0)
        for i in range(14):
            print("\\hline")
            print '%f &  %f &' % (self.x_f_t[i], self.y_f_t[i])
            print "  \\\\ "
        gen_tex.end_table()
        for position, item in enumerate(self.t_calc):
            if item == 24.00000000000002:
                idx_t_calc = position
        self.x_t_s = calc_burn_change_x(idx_t_calc, self.L10, self.L20, self.D20, self.D30)
        self.y_t_s = calc_burn_change_y(idx_t_calc, self.D10_, self.D20, self.D30)

        gen_tex.begin_tableN4(24)
        for i in range(14):
            print("\\hline")
            print '%f &  %f &' % (self.x_t_s[i], self.y_t_s[i])
            print "  \\\\ "

        gen_tex.end_table()
        print("\\end{center}")
        gen_tex.right_signature('Table $N^o 4$: Table calculated data to construct a model of the engine combustion charge\\\\Table data validation through the function IF')

    def print_s_graphics(self):  # change this graphics
        gen_tex.begin_graphic("Section 1, Section 2, initial values")
        gen_tex.add_section()
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (self.x_f_t[i], self.y_f_t[i])
        print '( %f , %f )' % (self.x_f_t[0], self.y_f_t[0])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 10$: Start burning charge (0 sec)')
        for position, item in enumerate(self.t_calc):
            if item == 10.799999999999988:
                idx_t_calc = position
        x_10 = calc_burn_change_x(idx_t_calc, self.L10, self.L20, self.D20, self.D30)
        y_10 = calc_burn_change_y(idx_t_calc, self.D10_, self.D20, self.D30)
        gen_tex.begin_graphic("Section 1, Section 2, initial values, form of charge at t = 10.08")
        gen_tex.add_section()
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (self.x_f_t[i], self.y_f_t[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (x_10[i], y_10[i])
        print '( %f , %f )' % (x_10[0], y_10[0])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 11$: Intermediate burning time charge (10.08 seconds)')

        for position, item in enumerate(self.t_calc):
            if item == 17.99999999999997:
                idx_t_calc = position
        x_18 = calc_burn_change_x(idx_t_calc, self.L10, self.L20, self.D20, self.D30)
        y_18 = calc_burn_change_y(idx_t_calc, self.D10_, self.D20, self.D30)
        gen_tex.begin_graphic(" Section 1, Section 2, initial values, form of charge at t = 18")
        gen_tex.add_section()
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (self.x_f_t[i], self.y_f_t[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (x_18[i], y_18[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 12$: Intermediate burning time charge (18 sec)')
        gen_tex.begin_graphic("Section 1, Section 2, initial values, form of charge at t = 24")
        gen_tex.add_section()
        print("\\addplot[mark = none,line width = 0.05 cm, draw = blue] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (self.x_f_t[i], self.y_f_t[i])
        print("};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(14):
            print '( %f , %f )' % (self.x_t_s[i], self.y_t_s[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 13$: The final time of combustion of the charge (24 sec)')

    def print_building_profile_nozzle(self):
        gen_tex.table_building_profile_nozzle()
        for i in range(21):
            print '%d & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f \\\\' % (
            self.I[i], self.L_i[i], self.D_i[i], self.F_i[i], self.Fkr_Fi[i], self.lambda_i[i], self.gdf_qu_l[i], self.gdf_pi_l[i],
            self.gdf_tau_l[i], self.gdf_eps_l[i], self.diff_q_Fkr[i], self.P_[i], self.T[i], self.R_0[i], self.v[i])
        gen_tex.end_table()
        print("\\end{center}")
        gen_tex.right_signature('Table $N^o 5$: Data table to build the profile of the nozzle')
        gen_tex.begin_graphic("P")
        print("\\addplot [mark = none,line width = 0.05 cm, draw = red] coordinates{")
        for i in range(21):
            print '( %f , %d )' % (self.L_i[i], self.P_[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 14$: Schedule changes in pressure on the projected profile of the nozzle')
        gen_tex.begin_graphic("T")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(21):
            print '( %f , %f )' % (self.L_i[i], self.T[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 15$: STemperature curve projected to the profile nozzle')
        gen_tex.begin_graphic("v")
        print ("\\node[anchor=south west,inner sep=0] at (0,0) {\includegraphics[width=9cm, height=4cm]{fon.jpg}};")
        print("\\addplot[mark = none,line width = 0.05 cm, draw = red] coordinates {")
        for i in range(21):
            print '( %f , %f )' % (self.L_i[i], self.v[i])
        gen_tex.end_graphic()
        gen_tex.right_signature('Pic. $N^o 16$: Schedule change the speed of the combustion products in the projected nozzle profile')


def main():
    calc_course = CalcCourseWork()
    calc_course.calc_data()
    calc_course.calc_profile_nozzle()
    calc_course.print_initial_data()
    calc_course.print_calculated_data()
    calc_course.print_dimensioning()
    calc_course.print_graphics()
    calc_course.print_constr_model_combustion()
    calc_course.print_s_graphics()
    calc_course.print_building_profile_nozzle()


if __name__ == '__main__':
    main()
