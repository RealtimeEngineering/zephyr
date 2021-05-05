/*
 * Copyright (c) 2020 PHYTEC Messtechnik GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/util.h>
#include <drivers/gpio.h>
#include <modbus/modbus.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(mbc_sample, LOG_LEVEL_INF);

static int client_iface;

const static struct modbus_iface_param client_param = {
	.mode = MODBUS_MODE_RTU,
	.rx_timeout = 500000,
	.serial = {
		.baud = 115200,
		.parity = UART_CFG_PARITY_EVEN,
	},
};

static int init_modbus_client(void)
{
	const char iface_name[] = {DT_PROP(DT_INST(1, zephyr_modbus_serial), label)};

	client_iface = modbus_iface_get_by_name(iface_name);

	return modbus_init_client(client_iface, client_param);
}

void main(void)
{
	uint16_t holding_reg[8] = {'H', 'e', 'l', 'l', 'o'};
    uint16_t input_reg[8] = {};
	const uint8_t coil_qty = 3;
	uint8_t coil[1] = {0};
	const int32_t sleep = 250;
	static uint8_t node = 1;
	int err;


	if (init_modbus_client()) {
		LOG_ERR("Modbus RTU client initialization failed");
		return;
	}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
	while ( true ) {
	    for ( int n = 0; n < 7; n++ ) {
            holding_reg[n] = holding_reg[n+1];
	    }
        holding_reg[7] += 1;
        err = modbus_write_holding_regs(client_iface, node, 0, holding_reg,
                        ARRAY_SIZE(holding_reg));
        if (err != 0) {
            LOG_ERR("FC16 failed");
            //return;
        }
        k_msleep(500);
        err = modbus_read_holding_regs(client_iface, node, 8, input_reg,
                           ARRAY_SIZE(input_reg));
        if (err != 0) {
            LOG_ERR("FC03 failed with %d", err);
            //return;
        }

        LOG_HEXDUMP_INF(input_reg, sizeof(input_reg),
                "WR|RD holding register:");
        k_msleep(500);
    }
#pragma clang diagnostic pop

	while (true) {
		uint16_t addr = 0;

		err = modbus_read_coils(client_iface, node, 0, coil, coil_qty);
		if (err != 0) {
			LOG_ERR("FC01 failed with %d", err);
			return;
		}

		LOG_INF("Coils state 0x%02x", coil[0]);

		err = modbus_write_coil(client_iface, node, addr++, true);
		if (err != 0) {
			LOG_ERR("FC05 failed with %d", err);
			return;
		}

		k_msleep(sleep);
		err = modbus_write_coil(client_iface, node, addr++, true);
		if (err != 0) {
			LOG_ERR("FC05 failed with %d", err);
			return;
		}

		k_msleep(sleep);
		err = modbus_write_coil(client_iface, node, addr++, true);
		if (err != 0) {
			LOG_ERR("FC05 failed with %d", err);
			return;
		}

		k_msleep(sleep);
		err = modbus_read_coils(client_iface, node, 0, coil, coil_qty);
		if (err != 0) {
			LOG_ERR("FC01 failed with %d", err);
			return;
		}

		LOG_INF("Coils state 0x%02x", coil[0]);

		coil[0] = 0;
		err = modbus_write_coils(client_iface, node, 0, coil, coil_qty);
		if (err != 0) {
			LOG_ERR("FC15 failed with %d", err);
			return;
		}

		k_msleep(sleep);
	}
}
