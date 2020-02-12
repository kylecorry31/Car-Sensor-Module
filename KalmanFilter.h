#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

class KalmanFilter
{

  private:
    float e_est;
    float e_mea;
    float est;
    float q;

  public:

    /**
     * A kalman filter
     * @param e_mea the error in the measurement
     * @param e_est the error in the initial estimate
     * @param initial_est the initial estimate
     * @param q the error in the process
     */
    KalmanFilter(float e_mea, float e_est, float initial_est, float q)
    {
      this->e_mea = e_mea;
      this->e_est = e_est;
      this->est = initial_est;
      this->q = q;
    }

    /**
     * Filters a measurement and updates the estimate
     * @param measurement the new measurement
     * @return the estimated state
     */
    float filter(float measurement)
    {
      float kg = e_est / (e_est + e_mea);
      est = est + kg * (measurement - est);
      e_est = (1 - kg) * (e_est + q);
      return est;
    }
  
};

#endif
