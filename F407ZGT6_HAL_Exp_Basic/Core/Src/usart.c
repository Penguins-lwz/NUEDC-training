/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
const char UART_Tx1E2[] = "0---------1---------2---------3---------4---------5---------6---------7---------8---------9---------";
const char UART_Tx1E4[] = "000-------001-------002-------003-------004-------005-------006-------007-------008-------009-------010-------011-------012-------013-------014-------015-------016-------017-------018-------019-------020-------021-------022-------023-------024-------025-------026-------027-------028-------029-------030-------031-------032-------033-------034-------035-------036-------037-------038-------039-------040-------041-------042-------043-------044-------045-------046-------047-------048-------049-------050-------051-------052-------053-------054-------055-------056-------057-------058-------059-------060-------061-------062-------063-------064-------065-------066-------067-------068-------069-------070-------071-------072-------073-------074-------075-------076-------077-------078-------079-------080-------081-------082-------083-------084-------085-------086-------087-------088-------089-------090-------091-------092-------093-------094-------095-------096-------097-------098-------099-------100-------101-------102-------103-------104-------105-------106-------107-------108-------109-------110-------111-------112-------113-------114-------115-------116-------117-------118-------119-------120-------121-------122-------123-------124-------125-------126-------127-------128-------129-------130-------131-------132-------133-------134-------135-------136-------137-------138-------139-------140-------141-------142-------143-------144-------145-------146-------147-------148-------149-------150-------151-------152-------153-------154-------155-------156-------157-------158-------159-------160-------161-------162-------163-------164-------165-------166-------167-------168-------169-------170-------171-------172-------173-------174-------175-------176-------177-------178-------179-------180-------181-------182-------183-------184-------185-------186-------187-------188-------189-------190-------191-------192-------193-------194-------195-------196-------197-------198-------199-------200-------201-------202-------203-------204-------205-------206-------207-------208-------209-------210-------211-------212-------213-------214-------215-------216-------217-------218-------219-------220-------221-------222-------223-------224-------225-------226-------227-------228-------229-------230-------231-------232-------233-------234-------235-------236-------237-------238-------239-------240-------241-------242-------243-------244-------245-------246-------247-------248-------249-------250-------251-------252-------253-------254-------255-------256-------257-------258-------259-------260-------261-------262-------263-------264-------265-------266-------267-------268-------269-------270-------271-------272-------273-------274-------275-------276-------277-------278-------279-------280-------281-------282-------283-------284-------285-------286-------287-------288-------289-------290-------291-------292-------293-------294-------295-------296-------297-------298-------299-------300-------301-------302-------303-------304-------305-------306-------307-------308-------309-------310-------311-------312-------313-------314-------315-------316-------317-------318-------319-------320-------321-------322-------323-------324-------325-------326-------327-------328-------329-------330-------331-------332-------333-------334-------335-------336-------337-------338-------339-------340-------341-------342-------343-------344-------345-------346-------347-------348-------349-------350-------351-------352-------353-------354-------355-------356-------357-------358-------359-------360-------361-------362-------363-------364-------365-------366-------367-------368-------369-------370-------371-------372-------373-------374-------375-------376-------377-------378-------379-------380-------381-------382-------383-------384-------385-------386-------387-------388-------389-------390-------391-------392-------393-------394-------395-------396-------397-------398-------399-------400-------401-------402-------403-------404-------405-------406-------407-------408-------409-------410-------411-------412-------413-------414-------415-------416-------417-------418-------419-------420-------421-------422-------423-------424-------425-------426-------427-------428-------429-------430-------431-------432-------433-------434-------435-------436-------437-------438-------439-------440-------441-------442-------443-------444-------445-------446-------447-------448-------449-------450-------451-------452-------453-------454-------455-------456-------457-------458-------459-------460-------461-------462-------463-------464-------465-------466-------467-------468-------469-------470-------471-------472-------473-------474-------475-------476-------477-------478-------479-------480-------481-------482-------483-------484-------485-------486-------487-------488-------489-------490-------491-------492-------493-------494-------495-------496-------497-------498-------499-------500-------501-------502-------503-------504-------505-------506-------507-------508-------509-------510-------511-------512-------513-------514-------515-------516-------517-------518-------519-------520-------521-------522-------523-------524-------525-------526-------527-------528-------529-------530-------531-------532-------533-------534-------535-------536-------537-------538-------539-------540-------541-------542-------543-------544-------545-------546-------547-------548-------549-------550-------551-------552-------553-------554-------555-------556-------557-------558-------559-------560-------561-------562-------563-------564-------565-------566-------567-------568-------569-------570-------571-------572-------573-------574-------575-------576-------577-------578-------579-------580-------581-------582-------583-------584-------585-------586-------587-------588-------589-------590-------591-------592-------593-------594-------595-------596-------597-------598-------599-------600-------601-------602-------603-------604-------605-------606-------607-------608-------609-------610-------611-------612-------613-------614-------615-------616-------617-------618-------619-------620-------621-------622-------623-------624-------625-------626-------627-------628-------629-------630-------631-------632-------633-------634-------635-------636-------637-------638-------639-------640-------641-------642-------643-------644-------645-------646-------647-------648-------649-------650-------651-------652-------653-------654-------655-------656-------657-------658-------659-------660-------661-------662-------663-------664-------665-------666-------667-------668-------669-------670-------671-------672-------673-------674-------675-------676-------677-------678-------679-------680-------681-------682-------683-------684-------685-------686-------687-------688-------689-------690-------691-------692-------693-------694-------695-------696-------697-------698-------699-------700-------701-------702-------703-------704-------705-------706-------707-------708-------709-------710-------711-------712-------713-------714-------715-------716-------717-------718-------719-------720-------721-------722-------723-------724-------725-------726-------727-------728-------729-------730-------731-------732-------733-------734-------735-------736-------737-------738-------739-------740-------741-------742-------743-------744-------745-------746-------747-------748-------749-------750-------751-------752-------753-------754-------755-------756-------757-------758-------759-------760-------761-------762-------763-------764-------765-------766-------767-------768-------769-------770-------771-------772-------773-------774-------775-------776-------777-------778-------779-------780-------781-------782-------783-------784-------785-------786-------787-------788-------789-------790-------791-------792-------793-------794-------795-------796-------797-------798-------799-------800-------801-------802-------803-------804-------805-------806-------807-------808-------809-------810-------811-------812-------813-------814-------815-------816-------817-------818-------819-------820-------821-------822-------823-------824-------825-------826-------827-------828-------829-------830-------831-------832-------833-------834-------835-------836-------837-------838-------839-------840-------841-------842-------843-------844-------845-------846-------847-------848-------849-------850-------851-------852-------853-------854-------855-------856-------857-------858-------859-------860-------861-------862-------863-------864-------865-------866-------867-------868-------869-------870-------871-------872-------873-------874-------875-------876-------877-------878-------879-------880-------881-------882-------883-------884-------885-------886-------887-------888-------889-------890-------891-------892-------893-------894-------895-------896-------897-------898-------899-------900-------901-------902-------903-------904-------905-------906-------907-------908-------909-------910-------911-------912-------913-------914-------915-------916-------917-------918-------919-------920-------921-------922-------923-------924-------925-------926-------927-------928-------929-------930-------931-------932-------933-------934-------935-------936-------937-------938-------939-------940-------941-------942-------943-------944-------945-------946-------947-------948-------949-------950-------951-------952-------953-------954-------955-------956-------957-------958-------959-------960-------961-------962-------963-------964-------965-------966-------967-------968-------969-------970-------971-------972-------973-------974-------975-------976-------977-------978-------979-------980-------981-------982-------983-------984-------985-------986-------987-------988-------989-------990-------991-------992-------993-------994-------995-------996-------997-------998-------999-------";

const uint32_t UART_BaudRateValue[12] = {
	2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 576000, 921600, 1152000
};

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream5;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmatx);
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void myUART_Start_Receive_DMA(myUART_HandleTypeDef *myhuart)
{
	memset(myhuart->RxMsg, 0, UART_BufSize);
	HAL_UARTEx_ReceiveToIdle_DMA(myhuart->huart, (uint8_t *)myhuart->RxMsg, UART_BufSize - 1);
}

void myUART_Transmit_DMA(myUART_HandleTypeDef *myhuart, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	while (myhuart->huart->gState != HAL_UART_STATE_READY || myhuart->huart->hdmatx->State != HAL_DMA_STATE_READY);
	int Size = vsnprintf(myhuart->TxMsg, UART_BufSize, format, ap);
	va_end(ap);
	HAL_UART_Transmit_DMA(myhuart->huart, (uint8_t *)myhuart->TxMsg, Size < UART_BufSize ? Size : (UART_BufSize - 1));
}

void myUART_SetBaudRate(myUART_HandleTypeDef *myhuart)
{
	WRITE_REG(myhuart->huart->Instance->BRR, 84000000.0 / UART_BaudRateValue[myhuart->idx] + 0.5);
}

/* USER CODE END 1 */