import sys
import ssl
import json
import tempfile
import http.client
from datetime import datetime
from typing import Optional, Union, List

class chonnect:
    """
    Initiates a connection object with **ClickHouse**  
    Username and password have to be provided at construction.

    ```python
    new_connection = chonnect('username', 'password')
    ```

    Other parameters are set as default:
    - `url`       = *clickhouse.r99.no*
    - `port`      = *8443*
    - `timeout`   = *15 seconds*
    - `ctx`       = **None**

    If no SSL context as `ctx` is given, a default client certificate chain will be used.

    No need to use `chonnect.connect()` after initiation, 
    as `chonnect.dr()` and `chonnect.query()` connect automatically.

    Remember to disconnect with `chonnect.disconnect()` when done.
    """
    __fullchain_content = """-----BEGIN CERTIFICATE-----
MIIB1zCCAX2gAwIBAgIUetk/dfIj+XLoTuPXGo9zvpEDuVgwCgYIKoZIzj0EAwIw
RDELMAkGA1UEBhMCTk8xETAPBgNVBAoMCE9za2FyIEFTMRMwEQYDVQQLDApPcGVy
YXRpb25zMQ0wCwYDVQQDDARPSVgxMB4XDTI0MTAxODE4MTk0NVoXDTI3MDcxNDE4
MTk0NVowPTELMAkGA1UEBhMCTk8xDjAMBgNVBAoMBW9za2FyMQ4wDAYDVQQLDAVv
c2thcjEOMAwGA1UEAwwFb3NrYXIwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAATc
z1la4k3RiRgiS4xLUZau21kIBT2RFhVJ8d+D3GH5HnSzg1xvYxqOd3V9y9ao7SaN
JFD9G8jMwNa/feZkChW4o1QwUjAQBgNVHREECTAHggVvc2thcjAdBgNVHQ4EFgQU
HeCRT3k42zf10fYdVdgczB8c6KYwHwYDVR0jBBgwFoAUznH3LUYrkMVXXGL9FuCq
b308skswCgYIKoZIzj0EAwIDSAAwRQIhAP5jp/DVLGPD9A5Scfoxbr3cLEdhzk4n
fGurlTk+7OVhAiBjGKbyILQ0A29TJTIkb1vgSxxAOQGfgjfHrNeQ5MTohQ==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIB9DCCAZqgAwIBAgIUb52coGjFRwi19j/kGtymy57cVc8wCgYIKoZIzj0EAwIw
SzELMAkGA1UEBhMCTk8xETAPBgNVBAoMCE9za2FyIEFTMRMwEQYDVQQLDApPcGVy
YXRpb25zMRQwEgYDVQQDDAtPc2thclJvb3RDQTAeFw0yNDA2MjQwMDI1MjZaFw0z
NDA2MjIwMDI1MjZaMEQxCzAJBgNVBAYTAk5PMREwDwYDVQQKDAhPc2thciBBUzET
MBEGA1UECwwKT3BlcmF0aW9uczENMAsGA1UEAwwET0lYMTBZMBMGByqGSM49AgEG
CCqGSM49AwEHA0IABGb0AK8OFDhQe7hGGQTnxfAfrOGahmcV5Pf37dAKT+2HFz7g
YBX4BFyDN6HkwkA0GXeD8f/gusWUq+akpy3fSs2jYzBhMA8GA1UdEwQIMAYBAf8C
AQAwDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBTOcfctRiuQxVdcYv0W4KpvfTyy
SzAfBgNVHSMEGDAWgBRmf/DmlpZyE9W+2O37q2P683WW1DAKBggqhkjOPQQDAgNI
ADBFAiEArKFFQo7/qWNJQNhYBh6J8tOSBUEIp0REp2riJesplWUCIFNmY2z25lWw
3AwXTssZ3LpagOBuCZHS8vzybDHsOEvS
-----END CERTIFICATE-----
-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgTd7D+/rQNFJ7W4kC
WqTBGSM52fe5HjeWXXxUTuFh+5KhRANCAATcz1la4k3RiRgiS4xLUZau21kIBT2R
FhVJ8d+D3GH5HnSzg1xvYxqOd3V9y9ao7SaNJFD9G8jMwNa/feZkChW4
-----END PRIVATE KEY-----
"""
    url = "clickhouse.r99.no"
    port = 8443
    __ctx = None
    __user = None
    __pass = None
    timeout = 15

    __connection_open = False

    def __init__(self, username: str, 
                 password: str, 
                 url: str = "clickhouse.r99.no", 
                 port: int = 8443, 
                 timeout: int = 15, 
                 ctx: Optional[ssl.SSLContext] = None):

        self.url = url
        self.port = port
        self.__user = username
        self.__pass = password
        self.__ctx = ctx
        self.timeout = timeout

        if self.__ctx == None:
            with tempfile.NamedTemporaryFile(delete=True) as tmp_cert:
                tmp_cert.write(self.__fullchain_content.encode())
                tmp_cert.flush()
                    
                new_context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
                new_context.load_cert_chain(certfile=tmp_cert.name)
                self.__ctx = new_context

        self.__headers = {
            'X-ClickHouse-User': self.__user,
            'X-ClickHouse-Key': self.__pass,
            'Content-Type': 'application/json'
        }

    def __run_query(self, query: str) -> Union[str, bool]:
        """
        Runs the given SQL query and returns the result in JSON format.

        **Parameters:**
        1. `query` (str): *The SQL query string to be executed*

        **Returns:**
        1. `str`: *The query result in JSON format if successful*
        2. `bool`: *False if an error occurs*
        """
        query_stripped_lower = query.strip().lower()
        if not query_stripped_lower.endswith("format json"):
            query = query_stripped_lower + " FORMAT JSON"

        try:
            self.local_connection.request("POST", "/", body=query.encode(), headers=self.__headers)
            response = self.local_connection.getresponse()
            full_data = response.read().decode()
            data = json.loads(full_data).get('data', [])
            return json.dumps(data, indent=4)
        except Exception as e:
            print(f'Requesting query from {self.url}:{self.port} failed with: {e}')
            return False

    def _remove_milliseconds(self, dt: Union[str, datetime]) -> Union[str, datetime]:
        """
        Removes milliseconds from a datetime object or string.

        **Parameters:**
        1. `dt` (str | datetime): *The datetime object or string*

        **Returns:**
        1. `str`: *A datetime string without milliseconds*
        2. `bool`: *False if the conversion fails*
        """
        if isinstance(dt, datetime):
            return datetime.strftime(dt, '%Y-%m-%dT%H:%M:%S')
        elif isinstance(dt, str):
            return datetime.strptime(dt, '%Y-%m-%dT%H:%M:%S')

    def _test_connection(self, connection: http.client.HTTPSConnection) -> bool:
        """
        Tests the connection to ClickHouse.

        **Parameters:**  
        1. `connection` (http.client.HTTPSConnection): *The connection object*

        **Returns:**  
        1. `bool`: *True if the connection is successful, False otherwise*
        """
        ret = None
        try:
            connection.request("GET", "/", headers=self.__headers)
            response = connection.getresponse()
            if response.read() == b'Ok.\n':
                ret = True
            else:
                print(f'Testing connction to {self.url}:{self.port} failed with not Ok:\n{response.read().decode()}', file=sys.stderr)
                ret = False
                connection.close()
        except Exception as e:
            print(f'Testing connection failed with exception: {e}', file=sys.stderr)
            ret = False
            connection.close()

        return ret

    def connect(self) -> Union[http.client.HTTPSConnection, bool]:
        """
        Tries to establish a connection to the ClickHouse server  
        This is normally not needed. See `chonnect.dr()` or `chonnect.query()` instead

        **Returns:**
        1. `http.client.HTTPSConnection`: *The connection object if successful*  
        2. `bool`: *False if the connection fails*  
        """
        if not self.__connection_open:
            try:
                conn = http.client.HTTPSConnection(self.url, self.port, context=self.__ctx, timeout=self.timeout)
                if self._test_connection(conn):
                    self.local_connection = conn
                    self.__connection_open = True
                    return conn
                else:
                    print(f'Test connection failed', file=sys.stderr)
                    return False
            except Exception as e:
                print(f'Opening connection to {self.url}:{self.port} failed with exception: {e}', file=sys.stderr)
                return False
        else:
            return False

    def disconnect(self, 
                   connection: Optional[http.client.HTTPSConnection] = None
        ) -> bool:
        """
        Disconnects from the ClickHouse server if a connection is open  
        Specifying connection object is not needed

        **Parameters**:  
        1. `connection` (http.client.HTTPSConnection, optional): *The connection object to disconnect. Defaults to None*

        **Returns**:  
        1. `bool`: *True if disconnection is successful, False otherwise*
        """

        if connection == None:
            connection = self.local_connection
        else:
            print(f'No connections to close', file=sys.stderr)
            return False

        if self.__connection_open:
            try:
                connection.close()
                self.__connection_open = False
                return True
            except Exception as e:
                print(f'Closing connection to {self.url}:{self.port} failed with:\n{e}', file=sys.stderr)
                return False
        else:
            print(f'No open connections. Doing nothing', file=sys.stderr)
            return False



    def query(self, query_str: str) -> Union[str, bool]:
        """
        Runs a custom query on the ClickHouse server.

        **Parameters:**  
        1. `query_str` (str): *The SQL query string to execute*

        **Returns:**  
        1. `str`: *JSON-formatted result if successful*
        2. `bool`: *False if an error occurs*

        **Example:**  
        ```python
        connection = chonnect('username', 'password')
        result = connection.query("SELECT bolt FROM sb.access LIMIT 10")```
        connection.disconnect()
        """
        if self.__connection_open == False:
            if self.connect() == False:
                print(f'Something wrong happened here (self.query)', file=sys.stderr)
                return False
            else:
                self.__connection_open = True

        return self.__run_query(query_str)

    

    def dr(self, 
           param_name: str, 
           param: Union[str, List[str]], 
           start_date: Union[str, datetime], 
           stop_date: Union[str, datetime]
        ) -> Union[str, bool]:
        """
        Constructs and runs a query for dynamic requests (DR) based on the given parameter.

        **Parameters:**
        1. `param_name` (str): *The field to query (e.g., 'bolt', 'env')*
        2. `param` (str | list of str): *The value(s) to query against*
        3. `start_date` (str | datetime): *The start datetime for the query. Should be in ISO 8601 format*
        4. `stop_date` (str | datetime): *The end datetime for the query. Should be in ISO 8601 format*

        **Returns:**
        1. `str`: *JSON result if the query is successful*
        2. `bool`: *False if an error occurs*

        **Example:**
        ```python
        connection = chonnect('username', 'password')
        result = connection.dr('bolt', 'apollo_15785', '2024-01-01 00:00:00', '2024-12-31 23:59:59')
        connection.disconnect()
        ```
        """
        if self.__connection_open == False:
            if self.connect() == False:
                print(f'Something wrong happened here (self.get_dr)', file=sys.stderr)
                return False
            else:
                self.__connection_open = True

        start_date = self._remove_milliseconds(start_date)
        stop_date = self._remove_milliseconds(stop_date)
        if start_date == False or stop_date == False: return False

        if isinstance(param, list):
            params = "', '".join(param)
        else:
            params = param

        query = f"""
            SELECT 
                bolt, 
                env, 
                sum(amount) as dr_raw, 
                formatReadableQuantity(dr_raw) as dr_readable 
            FROM dr.all 
                WHERE {param_name} in ('{params}') 
                AND time BETWEEN toDateTime('{start_date}') AND toDateTime('{stop_date}')
            GROUP BY bolt, env 
            FORMAT JSON"""

        return self.__run_query(query)

    def boltdr(self, 
               bolt: str, 
               start_date: Union[str, datetime], 
               stop_date: Union[str, datetime]
        ) -> Union[str, bool]:
        """Wrapper for `chonnect.dr()` to get bolt DR quickly  
        **Example:**
        ```python
        connection = chonnect('username', 'password')
        result = connection.boltdr('apollo_15785', '2024-01-01 00:00:00', '2024-12-31 23:59:59')
        connection.disconnect()
        ```
        """

        return self.dr('bolt', bolt, start_date, stop_date)

    def envdr(self, 
              env: str, 
              start_date: Union[str, datetime], 
              stop_date: Union[str, datetime]
        ) -> Union[str, bool]:
        """Wrapper for `chonnect.dr()` to get environment DR quickly  
        **Example:**
        ```python
        connection = chonnect('username', 'password')
        result = connection.envdr('apollo_15785', '2024-01-01 00:00:00', '2024-12-31 23:59:59')
        connection.disconnect()
        ```
        """

        return self.dr('env', env, start_date, stop_date)
