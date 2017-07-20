 /*!
 *  @brief  Define todas as métodos para funcionamento do módulo LED RGB
 *          para chip FRDM-K64F.
 *
 *  @file      dsf_PWM_ocp.cpp
 *  @version   1.0
 *  @date      13 July 2017
 *
 *  @section  HARDWARE & SOFTWARE
 *            +board      FRDM-KL25Z da NXP
 *            +processor  MKL25Z128VLK4 - ARM Cortex-M0+
 *            +compile    Kinetis design Studio IDE.
 *            +manual     L25P80M48SF0RM, Rev.3, September 2012.
 *
 *  @section  AUTHORS & DEVELOPMENT
 *            +institution  Universidade Federal do Amazonas
 *            +course       Engenharia da Computação / Engenharia Elétrica
 *            +professor    Miguel Grimm <miguelgrimm@gmail.com>
 *            +students     Versão inicial:
 *            	++ Luiz Henrique Sena	<coelho.luiz.sena@gmail.com>
 *              ++ Marcelo Ferreira  	<marcelofdeaquino@gmail.com>
 *              ++ Micael Pimentel		<micaelpimentel1@gmail.com>
 *              ++ Osmar Kabashima		<kabashimajr@gmail.com>
 *
 * @copyright   GNU General Public License (GNU GPL)
 *
 * @section     LICENSE
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include <dsf_PWM_ocp.h>

/*!
 *  @fn  dsf_PWM_ocp
 *
 *  @brief  Construtor que define inicialização do módulo PWM.
 */
dsf_PWM_ocp::dsf_PWM_ocp() {
	// TODO Auto-generated constructor stub

}

/*
 * =============================================================
 * |						TPM0							   |
 * =============================================================
 * | Canal 0 | Canal 1 | Canal 2 | Canal 3 | Canal 4 | Canal 5 |
 * =============================================================
 * |   PTA3  |   PTA4  |   PTA5  |         |         |   PTA0  |
 * -------------------------------------------------------------
 * |   PTC1  |   PTC2  |   PTC3  |   PTC4  |   PTC8  |   PTC9  |
 * -------------------------------------------------------------
 * |   PTD0  |   PTD1  |   PTD2  |   PTD3  |   PTD4  |   PTD5  |
 * -------------------------------------------------------------
 * |   PTE24 |   PTE25 |   PTE29 |   PTE30 |   PTE31 |         |
 * -------------------------------------------------------------
 *
 * =============================================================
 * |						TPM1							   |
 * =============================================================
 * | Canal 0 | Canal 1 | Canal 2 | Canal 3 | Canal 4 | Canal 5 |
 * =============================================================
 * |   PTA12 |   PTA13 |         |         |         |         |
 * -------------------------------------------------------------
 * |   PTB0  |   PTB1  |         |         |         |         |
 * -------------------------------------------------------------
 * |   PTE20 |   PTE21 |         |         |         |         |
 * -------------------------------------------------------------
 *
 * =============================================================
 * |						TPM2							   |
 * =============================================================
 * | Canal 0 | Canal 1 | Canal 2 | Canal 3 | Canal 4 | Canal 5 |
 * =============================================================
 * |   PTA1  |   PTA2  |         |         |         |         |
 * -------------------------------------------------------------
 * |   PTB2  |   PTB3  |         |         |         |         |
 * -------------------------------------------------------------
 * |   PTB18 |   PTB19 |         |         |         |         |
 * -------------------------------------------------------------
 * |   PTE22 |   PTE23 |         |         |         |         |
 * -------------------------------------------------------------
 */

/*!
 *  @fn  bindPeripheral
 *
 *  @brief  Configura o módulo PWM.
 *
 *  @remarks  Siglas e páginas do Manual de Referência K64F:
 *            - GPIO: General Purpose Input/Output.
 *            - SimSCGC: System Device Gating Control Register. Pág. 307 - 319.
 *            - SIM_SOPT: System Options Register. Pág 161 - 163
 */
bool dsf_PWM_ocp::bindPeripheral(TPM_MemMapPtr tpm){
	this->tpm = tpm;

	if(this->tpm == TPM0){
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	}
	else if(this->tpm == TPM1){
		SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
	}
	else if(this->tpm == TPM2){
		SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
	}
	else{
		return false;
	}

	// Configurado para o relógio de clock MCGFLLCLK
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(TPM_PLLFLL);

	// Configurando interrupção do contador na borda de subida
	this->tpm->SC &= ~TPM_SC_CPWMS_MASK;

	return true;
}

/*!
 *  @fn  bindChannel
 *
 *  @brief  Configura o canal do TMP.
 *
 */
bool dsf_PWM_ocp::bindChannel(uint16_t channel){

	this->channel=channel;

	// Configurando modo do canal
	TPM_CnSC_REG(this->tpm, this->channel) |= TPM_PWM_H;
}

/*!
 *  @fn  setFrequence
 *
 *  @brief  Configura a frequência do TMP.
 *
 */
bool dsf_PWM_ocp::setFrequence(uint16_t freq){
	this->tpm->MOD = (20971520)/(128*freq);
	return true;
}

/*!
 *  @fn  bindPort
 *
 *  @brief  Configura a porta GPIO usada no módulo PWM.
 *
 *  @remarks  Siglas e páginas do Manual de Referência K64F:
 *            - GPIO: General Purpose Input/Output.
 *            - SimSCGC: System Device Gating Control Register. Pág. 307 - 319.
 */
bool dsf_PWM_ocp::bindPort(GPIO_MemMapPtr gpio, uint8_t pin){

	this->gpio=gpio;
	this->pin=pin;

	if(this->tpm == TPM0){
		// PTA3 - CH0
		// PTA4 - CH1
		// PTA5 - CH2
		// PTA0 - CH5
		if(this->gpio == GPIOA){
			if((this->channel<=2)||(this->channel==5)){
				if((this->pin>=3) || (this->pin<=5)){
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORT_PCR_REG(PORTA_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		// PTC1	- CH0
		// PTC2	- CH1
		// PTC3	- CH2
		// PTC4	- CH3
		// PTC8 - CH4
		// PTC9 - CH5
		else if(this->gpio == GPIOC){
			if(this->channel<=5){
				if((this->pin>=1 || this->pin<=4) || (this->pin==8) || (this->pin==9)){
					SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
					PORT_PCR_REG(PORTC_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		// PTD0 - CH0
		// PTD1 - CH1
		// PTD2 - CH2
		// PTD3 - CH3
		// PTD4 - CH4
		// PTD5 - CH5
		else if(this->gpio == GPIOD){
			if(this->channel<=5){
				if(this->pin<=5){
					SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
					PORT_PCR_REG(PORTD_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		// PTE24 - CH0
		// PTE25 - CH1
		// PTE29 - CH2
		// PTE30 - CH3
		// PTE31 - CH4
		else if(this->gpio == GPIOE){
			if(this->channel<=4){
				if( (this->pin>=24 || this->pin<=25) || (this->pin>=29 || this->pin<=31) ){
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORT_PCR_REG(PORTE_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if(this->tpm == TPM1){
		if(this->channel <= 1){
			// PTA12 - CH0
			// PTA13 - CH1
			if(this->gpio == GPIOA){
				if(this->pin>=12 || this->pin<=13){
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORT_PCR_REG(PORTA_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTB0 - CH0
			// PTB1 - CH1
			else if(this->gpio == GPIOB){
				if(this->pin<=1){
					SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
					PORT_PCR_REG(PORTB_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTE20 - CH0
			// PTE21 - CH1
			else if(this->gpio == GPIOE){
				if(this->pin>=20 || this->pin<=21){
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORT_PCR_REG(PORTE_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if(this->tpm == TPM2){
		if(this->channel <= 1){
			// PTA1 - CH0
			// PTA2 - CH1
			if(this->gpio == GPIOA){
				if(this->pin>=1 || this->pin<=2){
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORT_PCR_REG(PORTA_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTB2 - CH0
			// PTB3 - CH1
			// PTB18 - CH0
			// PTB19 - CH1
			else if(this->gpio == GPIOB){
				if((this->pin>=2||this->pin<=3) || (this->pin>=18||this->pin<19)){
					SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
					PORT_PCR_REG(PORTB_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTE22 - CH0
			// PTE23 - CH1
			else if(this->gpio == GPIOE){
				if(this->pin>=22 || this->pin<=23){
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORT_PCR_REG(PORTE_BASE_PTR,this->pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;

	return true;
}

/*!
 *  @fn  bindPeripheral
 *
 *  @brief  Configura o duty cycle do sinal PWM.
 *
 */
void dsf_PWM_ocp::setDutyCycle(uint16_t dutyCicle){
	TPM_CnV_REG(this->tpm, this->channel) = (dutyCicle*(this->tpm->MOD))/100;
}

/*!
 *  @fn  enableOperation
 *
 *  @brief  Habilita o periférico para economizar energia.
 *
 */
void dsf_PWM_ocp::enableOperation(){
	// Configurado po incremento do contador para toda contagem do clock.
	// Valor do prescale configurado em 128
	this->tpm->SC |= TPM_SC_CMOD(TPM_CLK) | TPM_SC_PS(PS_128);
}

/*!
 *  @fn  disableOperation
 *
 *  @brief  Desabilita o periférico para economizar energia.
 *
 */
void dsf_PWM_ocp::disableOperation(){
	// Configurado po incremento do contador para toda contagem do clock.
	// Valor do prescale configurado em 128
	this->tpm->SC |= TPM_SC_CMOD(TPM_CLK_DIS);
}
