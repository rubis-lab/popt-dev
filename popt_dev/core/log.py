import logging


def new_logger(self, name='main'):
    logger = logging.getLogger(str(name))
    if not logger.handlers:
        logger.setLevel(logging.INFO)
        formatter = logging.Formatter(
            '%(asctime)s :: %(module)s :: %(funcName)s :: %(message)s')
        stream = logging.StreamHandler()
        stream.setFormatter(formatter)
        logger.addHandler(stream)
    return logger